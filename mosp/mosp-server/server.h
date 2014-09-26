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

	template <typename T>
	void Broadcast(const T& message);

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

template <typename T>
void Server::Broadcast(const T& message)
{
	unsigned char* data = new unsigned char[message.ByteSize()];
	message.SerializeToArray(data, message.ByteSize());

	ENetPacket* packet = enet_packet_create(data, message.ByteSize(), ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(server, 0, packet); // Handles the deallocation of the packet as well so we won't need to call enet_packet_destroy()

	delete data;
}

#endif