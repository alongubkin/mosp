#ifndef _H_SERVER
#define _H_SERVER

#if defined(_WIN32)
#include <winsock2.h>
#include <windows.h>
#endif

#include "mongo/client/dbclient.h"

#include <thread>
#include "enet/enet.h"
#include "Ticker.h"

class Server
{
public:
	Server(int port);
	~Server();

	void Run();

	bool IsRunning() { return isRunning; }
	const std::vector<Client*>& GetClients() const { return clients; }

	template <typename T>
	void Broadcast(const T& message);

	template <typename T>
	void Broadcast(const T& message, const Client* excludedClient);

private:
	ENetHost* server;
	bool isRunning;

	Ticker* ticker;
	std::thread tickerThread;

	mongo::DBClientConnection* db;

	unsigned int nextAvailableId = 0;

	std::vector<Client*> clients;

	void Listen();
	void OnConnect(const ENetEvent &evt);
	void OnReceive(const ENetEvent &evt);
	void OnDisconnect(const ENetEvent &evt);
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

template <typename T>
void Server::Broadcast(const T& message, const Client* excludedClient)
{
	for (auto it = clients.begin(); it != clients.end(); it++)
	{
		Client* client = *it;
		if (client != excludedClient)
		{
			client->Send(message);
		}
	}
}


#endif