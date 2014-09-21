#include <iostream>
#include <enet/enet.h>

int main()
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}

	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = 1234;

	ENetHost *server = enet_host_create(&address, // the address to bind the server host to
										2000,	  // allow up to 2000 clients
										2,		  // allow up to 2 channels to be used, 0 and 1
										0,		  // assume any amount of incoming bandwidth
										0);		  // assume any amount of outgoing bandwidth
	if (server == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet server host.\n");
		return EXIT_FAILURE;
	}

	enet_host_destroy(server);
	atexit(enet_deinitialize);
}