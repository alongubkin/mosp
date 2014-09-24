#pragma once

#include <string>
#include <hash_map>
#include "enet/enet.h"
#include "client.h"

class Server
{
public:
	Server(int port);
	~Server();

	
	void StartListen();
	
private:
	ENetHost* server;
	bool isRunning;
	std::hash_map<int, Client*> clients;

	void ProcessPacket(ENetPacket* packet, ENetPeer* peer);
};