#include "ticker.h"
#include "server.h"
#include "client.h"
#include <map>

void Ticker::Initialize()
{

}

void Ticker::Run()
{
	while (server->IsRunning())
	{
		auto clients = server->GetClientList();

		for (auto it = clients.begin(); it != clients.end(); ++it)
		{
			Client* c = (*it).second;
			
			//TODO Iterate on all of the clients and process their incoming packets
			
		}
	}
}
