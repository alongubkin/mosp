#ifndef _H_TICKER
#define _H_TICKER

#include "enet/enet.h"
#include "event_handler.h"

class Server;

class Ticker
{
public:
	Ticker(Server* server);
	~Ticker();

	void Run();
	
private:
	Server* server;
	EventHandler* eventHandler;

	template<typename T>
	T PacketToMessage(ENetPacket* packet);

	void HandlePacket(ENetPacket* packet);
};

template<typename T>
T Ticker::PacketToMessage(ENetPacket* packet)
{
	T message;
	if (!message.ParseFromArray(packet->data, packet->dataLength))
	{
		// TODO: throw exception
		assert("packet parsing error");
	}

	return message;
}

#endif