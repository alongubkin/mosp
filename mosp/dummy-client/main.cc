#include <iostream>
#include "enet/enet.h"
#include "proto/messages.pb.h"

int main()
{
	enet_initialize();

	ENetHost* client;
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

	ENetAddress address;
	ENetEvent event;
	ENetPeer* server;
	/* Connect to 127.0.0.1:1234. */
	enet_address_set_host(&address, "127.0.0.1");
	address.port = 1234;
	/* Initiate the connection, allocating the two channels 0 and 1. */
	server = enet_host_connect(client, &address, 2, 0);
	if (server == NULL)
	{
		fprintf(stderr, "No available peers for initiating an ENet connection.\n");
		exit(EXIT_FAILURE);
	}
	/* Wait up to 5 seconds for the connection attempt to succeed. */
	if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
	{
		printf("Connection to 127.0.0.1:1234 succeeded!\n");

		while (enet_host_service(client, &event, 1000) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				//OnConnect(event);
				break;

			case ENET_EVENT_TYPE_RECEIVE:
			{
				mosp::BaseMessage header;
				header.ParseFromArray(event.packet->data, event.packet->dataLength);
				std::cout << header.type() << std::endl;
				break;
			}

			case ENET_EVENT_TYPE_DISCONNECT:
				//OnDisconnect(event);
				break;
			}
		}

		getchar();
	}
	else
	{
		/* Either the 5 seconds are up or a disconnect event was */
		/* received. Reset the peer in the event the 5 seconds   */
		/* had run out without any significant event.            */
		enet_peer_reset(server);
		puts("Connection to 127.0.0.1:1234 failed.");
	}

	enet_host_destroy(client);
	enet_deinitialize();

	return 0;
}