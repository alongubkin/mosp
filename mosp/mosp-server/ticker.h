#ifndef _TICKER_H
#define _TICKER_H

#include "enet/enet.h"
#include "proto/messages.pb.h"

class Server;

class Ticker
{
public:
	Ticker(const Server* server) : server(server) {}
	~Ticker() {};
	
	void Run();
	
private:
	const Server* server;

	template<typename T>
	T PacketToMessage(ENetPacket* packet);

	void HandlePacket(ENetPacket* packet);
};

#endif