#include <iostream>
#include <enet/enet.h>
#include "server.h"



int main()
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}
	
	Server* server = new Server(1234);
	server->StartListen();

	
	atexit(enet_deinitialize);
}