#include "client.h"
#include "proto/messages.pb.h"

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
		exit(EXIT_FAILURE);
	}
}

Client::~Client()
{
	enet_host_destroy(client);
}

void Client::Connect(std::string ip, int port)
{
	ENetAddress address;
	enet_address_set_host(&address, ip.c_str());
	address.port = 1234;
	server = enet_host_connect(client, &address, 2, 0);

	if (server == NULL)
	{
		fprintf(stderr, "No available peers for initiating an ENet connection.\n");
		exit(EXIT_FAILURE);
	}
}

void Client::Run()
{
	ENetEvent event;
	isRunning = true;

	while (isRunning)
	{
		while (enet_host_service(client, &event, 1000) > 0)
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

void Client::OnConnect(ENetEvent& evt)
{
	printf("Connection to remote server succeeded!\n");

	mosp::JoinRequestMessage msg;
	msg.set_type(mosp::Type::JoinRequest); //Should make it default via proto
	msg.set_name("DummyClient");

	Send(msg);
}

void Client::OnReceive(ENetEvent& evt)
{
	
}

void Client::OnDisconnect(ENetEvent& evt)
{
	enet_peer_reset(server);
}

template <typename T>
void Client::Send(const T& message)
{
	unsigned char* data = new unsigned char[message.ByteSize()];
	message.SerializeToArray(data, message.ByteSize());

	ENetPacket* packet = enet_packet_create(data, message.ByteSize(), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(server, 0, packet); //Handles the deallocation of the packet as well so we won't need to call enet_packet_destroy()

	delete data;
}