#include "event_handler.h"
#include "server.h"
#include "logger.h"

EventHandler::EventHandler()
{

}

EventHandler::~EventHandler()
{

}

void EventHandler::OnConnectRequest(Server* server, Client* sender, const mosp::ConnectRequestMessage& message)
{
	sender->SetName(message.name());

	// Send an OK response
	mosp::ConnectResponseMessage responseMessage;
	responseMessage.set_type(mosp::Type::ConnectResponse);
	responseMessage.set_success(true);

	mosp::Vector2* vec2 = new mosp::Vector2();
	vec2->set_x(0);
	vec2->set_y(0);

	responseMessage.set_allocated_position(vec2);
	responseMessage.set_client_id(sender->GetId());

	sender->Send(message);

	// Notify all other players about this new player
	mosp::PlayerConnectMessage msg;
	msg.set_type(mosp::Type::PlayerConnect);
	msg.set_name(message.name());
	msg.set_client_id(sender->GetId());

	mosp::Vector2* spawnpoint = new mosp::Vector2();
	vec2->set_x(0);
	vec2->set_y(0);

	msg.set_allocated_position(spawnpoint);

	server->Broadcast(msg, sender);

	// Notify the new player about the already connected players
	auto clients = server->GetClients();

	for (auto it = clients.begin(); it != clients.end(); it++)
	{
		Client* client = *it;

		if (client != sender)
		{
			mosp::PlayerConnectMessage playerConnect;
			playerConnect.set_type(mosp::Type::PlayerConnect);
			playerConnect.set_client_id(client->GetId());
			playerConnect.set_allocated_position(new mosp::Vector2(client->GetTargetPosition()));
			playerConnect.set_name(message.name());

			client->Send(playerConnect);
		}
	}
}

void EventHandler::OnPlayerDisconnect(Server* server, Client* sender, const mosp::PlayerDisconnectMessage& message)
{

}

void EventHandler::OnPlayerMoved(Server* server, Client* sender, const mosp::PlayerMovedMessage& message)
{
	sender->SetTargetPosition(mosp::Vector2(message.position()));
	
	mosp::PlayerMovedMessage playerMoved;
	playerMoved.set_type(mosp::Type::PlayerMoved);
	playerMoved.set_client_id(sender->GetId());
	playerMoved.set_allocated_position(new mosp::Vector2(message.position()));

	Logger::Info("clientid: %d - position: %f, %f\n", sender->GetId(), message.position().x(), message.position().y());

	server->Broadcast(playerMoved, sender);
}