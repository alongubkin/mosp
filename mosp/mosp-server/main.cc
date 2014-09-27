#include "enet/enet.h"
#include "server.h"

int main()
{
	enet_initialize();

	Server* server = new Server(1234);
	server->Run();

	enet_deinitialize();
	return 0;
}