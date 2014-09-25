#include "ticker.h"
#include "server.h"
#include "client.h"
#include "proto/messages.pb.h"

void Ticker::Initialize()
{

}

void Ticker::Run()
{
	while (server->IsRunning())
	{
		auto clients = server->GetClients();

		for (auto it = clients.begin(); it != clients.end(); ++it)
		{
			auto queue = (*it)->GetQueue();
			
			const mosp::BaseMessage* message = nullptr;
			while ((message = queue->pop()) != nullptr)
			{
				// TODO: Handle message
				delete message;
			}
		}
	}
}
