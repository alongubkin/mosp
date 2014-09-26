#ifndef _CLIENT_H
#define _CLIENT_H

#include "enet/enet.h"
#include "proto/messages.pb.h"
#include "concurrent_queue.h"

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
	ConcurrentQueue<ENetPacket*>* GetQueue() { return &incomingPackets; }

	void HandleJoinRequestMessage(const mosp::JoinRequestMessage& message);
	void HandleMoveRequestMessage(const mosp::MoveRequestMessage& message);

private:
	int id = 0;
	ENetPeer* peer;
	Server* server;
	
	ConcurrentQueue<ENetPacket*> incomingPackets;

	mosp::Vector3* targetPosition;

	template <typename T>
	void Send(const T& message);
};

#endif