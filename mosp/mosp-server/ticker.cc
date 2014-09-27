#include "ticker.h"
#include "logger.h"
#include "server.h"

Ticker::Ticker(Server* server)
{
	this->server = server;
	eventHandler = new EventHandler();
}

Ticker::~Ticker()
{
	delete eventHandler;
}

void Ticker::Run()
{
	while (server->IsRunning())
	{
		auto clients = server->GetClients();

		for (auto it = clients.begin(); it != clients.end(); ++it)
		{
			auto queue = (*it)->CopyQueue();

			while (!queue.empty())
			{
				ENetPacket* packet = queue.front();
				queue.pop();

				HandlePacket(packet); // Deallocates packet as well...
			}
		}
	}
}

void Ticker::HandlePacket(ENetPacket* packet)
{
	Client* client = static_cast<Client*>(packet->userData);
	mosp::BaseMessage baseMessage = PacketToMessage<mosp::BaseMessage>(packet);

	switch (baseMessage.type())
	{
	case mosp::Type::ConnectRequest:
		eventHandler->OnConnectRequest(server, client, PacketToMessage<mosp::ConnectRequestMessage>(packet));
		break;

	case mosp::Type::PlayerMoved:
		eventHandler->OnPlayerMoved(server, client, PacketToMessage<mosp::PlayerMovedMessage>(packet));
		break;

	default:
		Logger::Info("Unknown message received!");
		break;
	}

	enet_packet_destroy(packet);
}