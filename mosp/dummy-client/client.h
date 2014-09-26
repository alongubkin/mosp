#ifndef _H_CLIENT
#define _H_CLIENT

#include <string>
#include "enet/enet.h"

class Client
{
public:
	Client();
	~Client();

	void Connect(std::string ip, int port);
	void Run();
	

private:
	ENetHost* client;
	ENetPeer* server;
	bool isRunning;

	void OnConnect(ENetEvent& evt);
	void OnReceive(ENetEvent& evt);
	void OnDisconnect(ENetEvent& evt);

	void Send(void* data, int dataLength, int channel);
};

#endif
