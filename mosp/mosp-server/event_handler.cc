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
	std::string tempName(message.name());
	tempName.append("_");
	tempName.append(std::to_string(sender->GetId()));

	sender->SetName(tempName);

	mosp::Vector2 spawnPoint;
	spawnPoint.set_x(0.0f);
	spawnPoint.set_y(0.0f);

	sender->SetTargetPosition(spawnPoint);

	// Send an OK response
	mosp::ConnectResponseMessage responseMessage;
	responseMessage.set_type(mosp::Type::ConnectResponse);
	responseMessage.set_success(true);
	responseMessage.set_allocated_position(new mosp::Vector2(sender->GetTargetPosition()));
	responseMessage.set_client_id(sender->GetId());
	responseMessage.set_name(tempName);

	sender->Send(responseMessage);

	// Notify all other players about this new player
	mosp::PlayerConnectMessage msg;
	msg.set_type(mosp::Type::PlayerConnect);
	msg.set_name(tempName);
	msg.set_client_id(sender->GetId());
	msg.set_allocated_position(new mosp::Vector2(sender->GetTargetPosition()));

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
			playerConnect.set_name(client->GetName());

			sender->Send(playerConnect);
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