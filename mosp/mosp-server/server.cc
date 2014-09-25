#include "server.h"
#include "proto/messages.pb.h"

Server::Server(int port)
{
	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = port;

	server = enet_host_create(&address, // the address to bind the server host to
		2000,	  // allow up to 2000 clients
		2,		  // allow up to 2 channels to be used, 0 and 1
		0,		  // assume any amount of incoming bandwidth
		0);		  // assume any amount of outgoing bandwidth

	if (server == NULL)
	{
		printf("error");
	}

	ticker = new Ticker(this);

	nextAvailableId = 0;
}

Server::~Server()
{
	delete ticker;

	enet_host_destroy(server);
	atexit(enet_deinitialize);
}

void Server::Run()
{
	isRunning = true;
	tickThread = std::thread(&Ticker::Run, ticker);

	Listen();

	tickThread.join();
	isRunning = false;
}

void Server::Listen()
{
	printf("Server is now online and listening to incoming traffic\n");

	ENetEvent event;

	while (isRunning)
	{
		int i;

		while ((i = enet_host_service(server, &event, 1000)) > 0)
		{
			switch (event.type)
			{
				case ENET_EVENT_TYPE_CONNECT:
					OnConnect(event);
					break;

				case ENET_EVENT_TYPE_RECEIVE:
					OnReceive(event);
					break;

				case ENET_EVENT_TYPE_DISCONNECT:
					OnDisconnect(event);
					break;
			}
		}
	}	
}

void Server::OnConnect(const ENetEvent &event)
{
	// Create a new client and push it to the client list
	Client *client = new Client(event.peer, nextAvailableId);
	clients.push_back(client);

	// Assign the client object to the peer
	event.peer->data = client;
	nextAvailableId++;
	printf("A new client connected from %x:%u assigned with id %d\n", event.peer->address.host, event.peer->address.port, nextAvailableId);

	//Temp
	mosp::JoinRequestMessage msg;
	msg.name = 
}

void Server::OnReceive(const ENetEvent &event)
{
	ProcessPacket(event.packet, event.peer);
	enet_packet_destroy(event.packet);
}

void Server::OnDisconnect(const ENetEvent &event)
{
	// Find the client using the peer object
	Client *client = static_cast<Client*>(event.peer->data);

	// Remove the client from the clients vector
	clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());

	printf("Client %d has disconnected\n", client->GetId());

	delete client;
	event.peer->data = nullptr;
}

void Server::ProcessPacket(const ENetPacket* packet, const ENetPeer* peer)
{
	mosp::BaseMessage* message;
	Client* client = static_cast<Client*>(peer->data);

	if (!message->ParseFromArray(packet->data, packet->dataLength))
	{
		printf("error\n");
	}

	client->QueueMessage(message);
}