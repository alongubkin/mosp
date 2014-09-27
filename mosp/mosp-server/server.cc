#include "server.h"
#include "logger.h"

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
		Logger::Error("Enet failed to create a host.");
	
	ticker = new Ticker(this);
}

Server::~Server()
{ 
	delete ticker;
	enet_host_destroy(server);
}

void Server::Run()
{
	isRunning = true;
	tickerThread = std::thread(&Ticker::Run, ticker);

	Listen();

	tickerThread.join();
}

void Server::Listen()
{
	Logger::Info("Server is now online and listening to incoming traffic\n");

	ENetEvent event;

	while (isRunning)
	{
		while (enet_host_service(server, &event, 1000) > 0)
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

void Server::OnConnect(const ENetEvent &evt)
{
	// Create a new client and push it to the client list
	Client* client = new Client(evt.peer, nextAvailableId);
	clients.push_back(client);

	// Assign the client object to the peer
	evt.peer->data = client;
	nextAvailableId++;

	Logger::Info("A new client connected from %x:%u assigned with id %d\n", evt.peer->address.host, evt.peer->address.port, nextAvailableId);
}

void Server::OnReceive(const ENetEvent &evt)
{
	Client* client = static_cast<Client*>(evt.peer->data);
	evt.packet->userData = client;
	client->QueuePacket(evt.packet);
}

void Server::OnDisconnect(const ENetEvent &evt)
{
	// Find the client using the peer object
	Client *client = static_cast<Client*>(evt.peer->data);

	// Remove the client from the clients vector
	clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());

	Logger::Info("Client %d has disconnected", client->GetId());

	delete client;
	evt.peer->data = nullptr;
}