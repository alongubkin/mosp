#ifndef _H_CLIENT
#define _H_CLIENT

#include <queue>
#include <mutex>
#include <string>
#include "enet/enet.h"
#include "proto/messages.pb.h"

class Client
{
public:
	Client(ENetPeer* peer, unsigned int clientId);
	~Client();
	
	unsigned int GetId() { return clientId; }
	void SetTargetPosition(mosp::Vector2 targetPosition) { this->targetPosition = targetPosition; }
	mosp::Vector2 GetTargetPosition() { return this->targetPosition; }
	void SetName(std::string name) { this->name = name; }
	std::string GetName() { return this->name; }

	void QueuePacket(ENetPacket* packet);
	std::queue<ENetPacket*> CopyQueue();

	template <typename T>
	void Send(const T& message);

private:
	ENetPeer* peer;
	unsigned int clientId;
	std::queue<ENetPacket*> incomingPackets;
	std::mutex incomingPacketsMutex;
	std::string name;
	mosp::Vector2 targetPosition;
};

template <typename T>
void Client::Send(const T& message)
{
	unsigned char* data = new unsigned char[message.ByteSize()];
	message.SerializeToArray(data, message.ByteSize());

	ENetPacket* packet = enet_packet_create(data, message.ByteSize(), ENET_PACKET_FLAG_RELIABLE);

	// Handles the deallocation of the packet as well 
	// so we won't need to call enet_packet_destroy()
	enet_peer_send(peer, 0, packet); 

	delete data;
}

#endif