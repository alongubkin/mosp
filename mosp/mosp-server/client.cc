#include "client.h"

Client::Client(ENetPeer* peer, unsigned int clientId)
{
	this->peer = peer;
	this->clientId = clientId;
}

Client::~Client()
{
}


void Client::QueuePacket(ENetPacket* packet)
{
	incomingPacketsMutex.lock();
	incomingPackets.push(packet);
	incomingPacketsMutex.unlock();
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