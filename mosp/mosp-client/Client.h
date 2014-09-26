#pragma once
#include <string>
#include "enet/enet.h"
#include "concurrent_queue.h"

class Client
{
public:
	Client();
	~Client();

	void Connect(std::string ip, int port);
	void Run();
	ConcurrentQueue<ENetPacket*>* GetQueue() { return &incomingPackets; }

private:
	ENetHost* client;
	ENetPeer* server;
	bool isRunning;
	ConcurrentQueue<ENetPacket*> incomingPackets;

	void OnConnect(ENetEvent& evt);
	void OnReceive(ENetEvent& evt);
	void OnDisconnect(ENetEvent& evt);

	

	template <typename T> 
	void Send(const T& message);
};