#include "event_handler.h"
#include "server.h"
#include "logger.h"
#include "password_utils.h"

EventHandler::EventHandler()
{

}

EventHandler::~EventHandler()
{

}

void EventHandler::OnConnectRequest(Server* server, Client* sender, const mosp::ConnectRequestMessage& message)
{
	mongo::DBClientConnection* db = server->GetDatabase();

	std::auto_ptr<mongo::DBClientCursor> cursor = db->query("mosp.users", 
		QUERY("username" << message.username()));
	
	if (cursor->more())
	{
		mongo::BSONObj user = cursor->next();
		
		std::string hash(user.getStringField("password"));
		std::string salt(user.getStringField("salt"));
		
		if (hash != mosp::HashPassword(message.password(), salt))
		{
			Logger::Info("User %s login attempt failed (invalid password).", message.username().c_str());
			Logger::Info("MAKE SURE TO CHANGE IT IN mosp-client/client.cc!");

			// Send an error response
			mosp::ConnectResponseMessage responseMessage;
			responseMessage.set_type(mosp::Type::ConnectResponse);
			responseMessage.set_success(false);
			responseMessage.set_error(mosp::CONNECT_REQUEST_ERROR::INVALID_LOGIN);
			sender->Send(responseMessage);

			return;
		}

		// Prevent login if the user is already connected
		std::string userId = user["_id"].OID().str();
		for (auto it = server->GetClients().begin(); it != server->GetClients().end(); it++)
		{
			if ((*it)->GetUserId() == userId)
			{
				mosp::ConnectResponseMessage responseMessage;
				responseMessage.set_type(mosp::Type::ConnectResponse);
				responseMessage.set_success(false);
				responseMessage.set_error(mosp::CONNECT_REQUEST_ERROR::NAME_EXISTS);
				sender->Send(responseMessage);

				Logger::Info("User %s tried to login even though he is already connected.", message.username().c_str());

				return;
			}
		}

		Logger::Info("User %s logged in successfully.", message.username().c_str());

		sender->SetName(message.username());

		mosp::Vector2 spawnPoint;
		spawnPoint.set_x(0.0f);
		spawnPoint.set_y(0.0f);

		sender->SetTargetPosition(spawnPoint);
		sender->SetUserId(userId);

		// Send an OK response
		mosp::ConnectResponseMessage responseMessage;
		responseMessage.set_type(mosp::Type::ConnectResponse);
		responseMessage.set_success(true);
		responseMessage.set_allocated_position(new mosp::Vector2(sender->GetTargetPosition()));
		responseMessage.set_client_id(sender->GetId());
		responseMessage.set_name(message.username());

		sender->Send(responseMessage);

		// Notify all other players about this new player
		mosp::PlayerConnectMessage msg;
		msg.set_type(mosp::Type::PlayerConnect);
		msg.set_name(message.username());
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
	else
	{
		Logger::Info("User %s login attempt failed (invalid username).", message.username().c_str());
		Logger::Info("MAKE SURE TO CHANGE IT IN mosp-client/client.cc!");

		// Send an error response
		mosp::ConnectResponseMessage responseMessage;
		responseMessage.set_type(mosp::Type::ConnectResponse);
		responseMessage.set_success(false);
		responseMessage.set_error(mosp::CONNECT_REQUEST_ERROR::INVALID_LOGIN);
		sender->Send(responseMessage);
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

	Logger::Info("clientid: %d - position: %f, %f", sender->GetId(), message.position().x(), message.position().y());

	server->Broadcast(playerMoved, sender);
}