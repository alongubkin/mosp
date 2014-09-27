#include "network_manager.h"
#include "game.h"
#include "client.h"
#include "player.h"
#include "controller_player.h"

NetworkManager::NetworkManager(Game* game)
	: _game(game)
{
	_client = new Client();
}

NetworkManager::~NetworkManager()
{
	delete _client;
}

void NetworkManager::Initialize()
{
	_client->Connect("127.0.0.1", 1234);
	_clientThread = std::thread(&Client::Run, _client);
}

void NetworkManager::Update()
{
	auto incomingPacketsQueue = _client->CopyQueue();

	while (!incomingPacketsQueue.empty())
	{
		ENetPacket* packet = incomingPacketsQueue.front();
		incomingPacketsQueue.pop();

		HandlePacket(packet);
	}
}

void NetworkManager::Close()
{
	_clientThread.join();
}

void NetworkManager::HandlePacket(ENetPacket* packet)
{
	mosp::BaseMessage baseMessage = PacketToMessage<mosp::BaseMessage>(packet);

	switch (baseMessage.type())
	{
	case mosp::Type::ConnectResponse:
		HandleConnectResponseMessage(PacketToMessage<mosp::ConnectResponseMessage>(packet));
		break;

	case mosp::Type::PlayerConnect:
		HandlePlayerConnectMessage(PacketToMessage<mosp::PlayerConnectMessage>(packet));
		break;

	case mosp::Type::PlayerMoved:
		HandlePlayerMovedMessage(PacketToMessage<mosp::PlayerMovedMessage>(packet));
		break;

	default:
		printf("unhandled message\n");
		break;
	}

	enet_packet_destroy(packet);
}

void NetworkManager::HandleConnectResponseMessage(const mosp::ConnectResponseMessage& message)
{
	_currentClientId = message.client_id();

	auto player = new ControllerPlayer(_game, message.name());
	player->SetPosition(message.position().x(), 5, message.position().y());

	_game->SetEntity(message.client_id(), player);
}

void NetworkManager::HandlePlayerConnectMessage(const mosp::PlayerConnectMessage& message)
{
	printf("New player joined with id %d\n", message.client_id());

	auto player = new Player(_game, message.name());
	player->SetPosition(message.position().x(), 5, message.position().y());

	_game->SetEntity(message.client_id(), player);
}

void NetworkManager::HandlePlayerMovedMessage(const mosp::PlayerMovedMessage& message)
{
	Entity* entity = _game->GetEntity(message.client_id());

	if (entity != nullptr)
	{
		entity->SetTarget(message.position().x(), message.position().y());
	}
}

template<typename T>
T NetworkManager::PacketToMessage(ENetPacket* packet)
{
	T message;
	if (!message.ParseFromArray(packet->data, packet->dataLength))
	{
		// TODO: throw exception
		assert("packet parsing error");
	}

	return message;
}

void NetworkManager::UpdateTargetPosition(float x, float y)
{
	mosp::Vector2 *position = new mosp::Vector2();
	position->set_x(x);
	position->set_y(y);

	mosp::PlayerMovedMessage message;
	message.set_type(mosp::Type::PlayerMoved);
	message.set_allocated_position(position);
	message.set_client_id(0); // The server ignores this value

	_client->Send(message);
}

