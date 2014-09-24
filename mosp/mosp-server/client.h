#pragma once

#include <queue>
#include <memory>
#include "enet/enet.h"

typedef unsigned char byte;

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

	void ProcessMessage();
};