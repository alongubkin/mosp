#include "stdafx.h"
#include "client.h"
#include "proto/messages.pb.h"
#include "config.h"

Client::Client()
{
	client = enet_host_create(NULL /* create a client host */,
		1 /* only allow 1 outgoing connection */,
		2 /* allow up 2 channels to be used, 0 and 1 */,
		57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
		14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);

	if (client == NULL)
	{
		fprintf(stderr, "An error occurred while trying to create an ENet client host.\n");
	}
}

Client::~Client()
{
	enet_host_destroy(client);
}

void Client::Connect(std::string ip, int port)
{
	if ( NumberOfTries > 0 )
		printf("Retrying #%d to %s:%d...\n", NumberOfTries, ip.c_str(), port);
	else
		printf("Connecting to %s:%d...\n", ip.c_str(), port);

	isConnected = false;
	connectStartTime = time(NULL);

	ENetAddress address;
	enet_address_set_host(&address, ip.c_str());
	address.port = port;
	server = enet_host_connect(client, &address, 2, 0);

	if (server == NULL)
	{
		fprintf(stderr, "No available peers for initiating an ENet connection.\n");
		
	}
}

void Client::Run()
{
	ENetEvent event;
	isRunning = true;

	while (isRunning)
	{
		// If we are trying to connect, check if it's time-out.
		if (server != NULL && !isConnected && time(NULL) - connectStartTime > 3)
		{
			// Get ip address string
			char destIpStr[15];
			enet_address_get_host_ip(&server->address, destIpStr, 15);


			// Try re-connecting...
			enet_peer_reset(server);
			NumberOfTries++;
			Connect(destIpStr, server->address.port);
			
		}
		while (enet_host_service(client, &event, 100) > 0)
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

	isRunning = false;
}

std::queue<ENetPacket*> Client::CopyQueue()
{
	incomingPacketsQueueMutex.lock();
	std::queue<ENetPacket*> _result(incomingPackets);
	std::queue<ENetPacket*> empty;
	std::swap(incomingPackets, empty);
	incomingPacketsQueueMutex.unlock();
	return _result;
}

void Client::OnConnect(ENetEvent& evt)
{
	isConnected = true;
	NumberOfTries = 0;

	printf("Connection to remote server succeeded!\n");

	mosp::ConnectRequestMessage msg;
	msg.set_type(mosp::Type::ConnectRequest); //Should make it default via proto
	msg.set_username(Config::GetProperty("username"));
	msg.set_password(Config::GetProperty("password"));

	Send(msg);
}

void Client::OnReceive(ENetEvent& evt)
{
	incomingPacketsQueueMutex.lock();
	incomingPackets.push(evt.packet);
	incomingPacketsQueueMutex.unlock();
}

void Client::OnDisconnect(ENetEvent& evt)
{
	enet_peer_reset(server);
}