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
}

Server::~Server()
{
	delete ticker;
	enet_host_destroy(server);
}

void Server::StartListen()
{
	printf("Server is now online and listening to incoming traffic");
	isRunning = true;
	int nextAvailableID = 0;
	ENetEvent event;

	tickThread = std::thread(&Ticker::Run, ticker);

	while (isRunning)
	{
		while (enet_host_service(server, &event, 1000) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
			{
				Client* c = new Client(event.peer, nextAvailableID);
				clients.insert(std::pair<int, Client*>(nextAvailableID, c));
				nextAvailableID++;
				event.peer->data = c;
				printf("A new client connected from %x:%u assigned with id %d", event.peer->address.host, event.peer->address.port, clients.size() - 1);
				break;
			}
			case ENET_EVENT_TYPE_RECEIVE:
			{
				ProcessPacket(event.packet, event.peer);
				enet_packet_destroy(event.packet);
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT:
			{
				Client* c = clients[event.data];
				event.peer->data = nullptr;
				int clientId = c->GetId();
				clients.erase(clientId);
				//delete c; //Delete the client after removed it reference from all other places
				//BroadcastPacket(std::make_shared<PacketPlayerDisconnected>(playerID), nullptr);
				printf("Client %d has disconnected", clientId);
				break;
			}
			}
		}
	}

	tickThread.join();
	isRunning = false;
}

void Server::ProcessPacket(ENetPacket* packet, ENetPeer* peer)
{
	Client* c = static_cast<Client*>(peer->data);

	mosp::BaseMessage base;

	if (!base.ParseFromArray(packet->data, packet->dataLength))
	{
		// TODO: throw exception
	}



	//Handler

	//JoinRequestHandler 
	

	// base.type() == mosp::Type::JoinRequest
}