#ifndef _CLIENT_H
#define _CLIENT_H

#include <queue>
#include <mutex>
#include "enet/enet.h"
#include "proto/messages.pb.h"

class Server;

class Client
{
public:
	Client(Server *server, ENetPeer* peer, int id) :
		server(server),
		peer(peer),
		id(id) {}

	~Client();
	
	int GetId() const { return id; }
	ENetPeer* GetPeer() const { return peer; }

	std::queue<ENetPacket*> CopyQueue();
	void QueuePacket(ENetPacket* packet);

	void HandleJoinRequestMessage(const mosp::JoinRequestMessage& message);
	void HandleMoveRequestMessage(const mosp::MoveRequestMessage& message);

private:
	int id = 0;
	ENetPeer* peer;
	Server* server;
	
	std::mutex incomingPacketsMutex;
	std::queue<ENetPacket*> incomingPackets;

	mosp::Vector3* targetPosition;

	template <typename T>
	void Send(const T& message);
};

template <typename T>
void Client::Send(const T& message)
{
	unsigned char* data = new unsigned char[message.ByteSize()];
	message.SerializeToArray(data, message.ByteSize());

	ENetPacket* packet = enet_packet_create(data, message.ByteSize(), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet); // Handles the deallocation of the packet as well so we won't need to call enet_packet_destroy()

	delete data;
}

#endif