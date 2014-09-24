#pragma once

#include <queue>
#include <memory>
#include "enet/enet.h"
#include "proto/messages.pb.h"

class Client
{
public:
	Client(ENetPeer* peer, int id) :
		peer(peer),
		id(id)
	{}

	~Client();
	
	void QueueMessage();

	int GetId() const { return id; }

private:
	ENetPeer* peer;
	int id;

	std::queue<mosp::BaseMessage*> incomingMessages;

	void ProcessMessage();
};