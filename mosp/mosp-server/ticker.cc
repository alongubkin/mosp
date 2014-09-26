#include "ticker.h"
#include "server.h"
#include "client.h"
#include "proto/messages.pb.h"

void Ticker::Run()
{
	while (server->IsRunning())
	{
		auto clients = server->GetClients();

		for (auto it = clients.begin(); it != clients.end(); ++it)
		{
			auto queue = (*it)->GetQueue();
			
			ENetPacket* message = nullptr;
			while ((message = queue->pop()) != nullptr)
			{
				HandlePacket(message);
			}
		}
	}
}

template<typename T>
T Ticker::PacketToMessage(ENetPacket* packet)
{
	T message;
	if (!message.ParseFromArray(packet->data, packet->dataLength))
	{
		// TODO: throw exception
		assert("packet parsing error");
	}

	return message;
}

void Ticker::HandlePacket(ENetPacket* packet)
{
	Client* client = static_cast<Client*>(packet->userData);
	mosp::BaseMessage baseMessage = PacketToMessage<mosp::BaseMessage>(packet);

	switch (baseMessage.type())
	{
		case mosp::Type::JoinRequest:
			client->HandleJoinRequestMessage(PacketToMessage<mosp::JoinRequestMessage>(packet));
			break;

		case mosp::Type::MoveRequest:
			client->HandleMoveRequestMessage(PacketToMessage<mosp::MoveRequestMessage>(packet));
			break;

		default:
			printf("unhandled message");
			break;
	}

	enet_packet_destroy(packet);
}
