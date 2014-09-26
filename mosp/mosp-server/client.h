#ifndef _CLIENT_H
#define _CLIENT_H

#include "enet/enet.h"
#include "proto/messages.pb.h"
#include "concurrent_queue.h"

class Client
{
public:
	Client(ENetPeer* peer, int id) :
		peer(peer),
		id(id) {}

	~Client();
	
	int GetId() const { return id; }
	ConcurrentQueue<ENetPacket*>* GetQueue() { return &incomingPackets; }

	void HandleJoinRequestMessage(const mosp::JoinRequestMessage& message);

private:
	int id = 0;
	ENetPeer* peer;

	ConcurrentQueue<ENetPacket*> incomingPackets;

	template <typename T>
	void Send(const T& message);
};

#endif