#pragma once

#include <string>
#include <hash_map>
#include <thread>
#include "enet/enet.h"
#include "client.h"
#include "ticker.h"

class Server
{
public:
	Server(int port);
	~Server();

	void StartListen();
	std::hash_map<int, Client*> GetClientList() const { return clients; }
	bool IsRunning() const { return isRunning; }

private:
	ENetHost* server;
	bool isRunning;
	std::hash_map<int, Client*> clients;

	void ProcessPacket(ENetPacket* packet, ENetPeer* peer);

	Ticker* ticker;
	std::thread tickThread;
};