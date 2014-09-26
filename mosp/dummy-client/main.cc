#include <iostream>
#include "client.h"

int main()
{
	enet_initialize();
	
	Client client;
	client.Connect("127.0.0.1", 1234);
	client.Run();

	enet_deinitialize();
	return 0;
}