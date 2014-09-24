#ifndef _CLIENT_H
#define _CLIENT_H

#include <queue>
#include <memory>
#include "enet/enet.h"
#include "proto/messages.pb.h"

class Client
{
public:
	Client(ENetPeer* peer, int id) :
		peer(peer),
		id(id) {}

	~Client();
	
	int GetId() const { return id; }
	void QueueMessage(const mosp::BaseMessage *message);

private:
	int id;
	ENetPeer* peer;

	std::queue<const mosp::BaseMessage*> incomingMessages;
};

#endif