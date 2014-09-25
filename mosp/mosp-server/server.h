#ifndef _SERVER_H
#define _SERVER_H

#include <string>
#include <vector>
#include <thread>
#include "enet/enet.h"
#include "client.h"
#include "ticker.h"

class Server
{
public:
	Server(int port);
	~Server();

	void Run();
	
	bool IsRunning() const { return isRunning; }

	const std::vector<Client*>& GetClients() const { return clients; }

private:
	bool isRunning = false;
	int nextAvailableId = 0;

	ENetHost *server;
	Ticker *ticker;

	std::vector<Client*> clients;
	std::thread tickThread;

	void Listen();

	void OnConnect(const ENetEvent &event);
	void OnReceive(const ENetEvent &event);
	void OnDisconnect(const ENetEvent &event);

	void ProcessPacket(const ENetPacket* packet, const ENetPeer* peer);
};

#endif