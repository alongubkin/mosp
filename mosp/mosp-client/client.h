#pragma once
#include <string>
#include <queue>
#include <mutex>
#include "enet/enet.h"

class Client
{
public:
	Client();
	~Client();

	void Connect(std::string ip, int port);
	void Run();

	std::queue<ENetPacket*> CopyQueue();

	template <typename T>
	void Send(const T& message);

private:
	ENetHost* client;
	ENetPeer* server;
	bool isRunning;
	bool isConnected = false;
	long connectStartTime;
	char NumberOfTries = 0;

	std::mutex incomingPacketsQueueMutex;
	std::queue<ENetPacket*> incomingPackets;

	void OnConnect(ENetEvent& evt);
	void OnReceive(ENetEvent& evt);
	void OnDisconnect(ENetEvent& evt);
};

template <typename T>
void Client::Send(const T& message)
{
	unsigned char* data = new unsigned char[message.ByteSize()];
	message.SerializeToArray(data, message.ByteSize());

	ENetPacket* packet = enet_packet_create(data, message.ByteSize(), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(server, 0, packet); //Handles the deallocation of the packet as well so we won't need to call enet_packet_destroy()

	delete data;
}