#ifndef _NETWORK_MANAGER_H
#define _NETWORK_MANAGER_H

#include <thread>
#include "proto/messages.pb.h"
#include "client.h"

class Game;

class NetworkManager
{
public:
	NetworkManager(Game* game);
	~NetworkManager();

	void Initialize();
	void Update();
	void Close();

	int GetCurrentClientId() { return _currentClientId; }
	void UpdateTargetPosition(float x, float y);

private:
	Game* _game;
	Client* _client;
	std::thread _clientThread;
	int _currentClientId = -1;

	void HandlePacket(ENetPacket* packet);

	template<typename T>
	T PacketToMessage(ENetPacket* packet);

	void HandleConnectResponseMessage(const mosp::ConnectResponseMessage& message);
	void HandlePlayerConnectMessage(const mosp::PlayerConnectMessage& message);
	void HandlePlayerMovedMessage(const mosp::PlayerMovedMessage& message);
};

#endif