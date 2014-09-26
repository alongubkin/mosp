#include "client.h"
#include "server.h"

Client::~Client() 
{
	delete peer;
}


std::queue<ENetPacket*> Client::CopyQueue()
{
	incomingPacketsMutex.lock();
	std::queue<ENetPacket*> _result(incomingPackets);
	std::queue<ENetPacket*> empty;
	std::swap(incomingPackets, empty);
	incomingPacketsMutex.unlock();
	return _result;
}

void Client::QueuePacket(ENetPacket* packet)
{
	incomingPacketsMutex.lock();
	incomingPackets.push(packet);
	incomingPacketsMutex.unlock();
}

void Client::HandleJoinRequestMessage(const mosp::JoinRequestMessage& message)
{
	printf("Name: %s\n", message.name().c_str());

	/*
	mosp::JoinResponseMessage response;
	response.set_success(true);
	response.set_client_id(this->GetId());
	response.set_allocated_position(new mosp::Vector3(*targetPosition));

	Send(response);
	*/

	targetPosition = new mosp::Vector3();
	targetPosition->set_x(0);
	targetPosition->set_y(5);
	targetPosition->set_z(0);

	mosp::JoinNotificationMessage notification;
	notification.set_type(mosp::Type::JoinNotification);
	notification.set_client_id(this->GetId());
	notification.set_allocated_position(new mosp::Vector3(*targetPosition));
	notification.set_name(message.name());
	
	server->Broadcast(notification);
}

void Client::HandleMoveRequestMessage(const mosp::MoveRequestMessage& message)
{
	this->targetPosition = new mosp::Vector3(message.position());

	mosp::MoveNotificationMessage notification;
	notification.set_type(mosp::Type::MoveNotification);
	notification.set_client_id(this->GetId());
	notification.set_allocated_position(new mosp::Vector3(message.position()));

	printf("clientid: %d - position: %f, %f, %f\n", GetId(), targetPosition->x(), targetPosition->y(), targetPosition->z());

	//server->Broadcast(notification);
}