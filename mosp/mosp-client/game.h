#pragma once
#include "stdafx.h"
#include <thread>
#include <hash_map>
#include "enet/enet.h"
#include "terrain.h"
#include "entity.h"
#include "controller_player.h"
#include "client.h"
#include "mpplayer.h"
#include "proto/messages.pb.h"

class Game
{

public:
	Game();
	~Game();

	void Run();
	Client* GetClient() const { return client; }

private:
	Ogre::Root* ogreRoot;
	Ogre::RenderWindow* window;
	Ogre::SceneManager* sceneManager;
	Ogre::Viewport* viewport;
	Ogre::Camera* camera;
	OIS::InputManager* inputManager;
	OIS::Keyboard* keyboard;
	OIS::Mouse* mouse;

	int currentPlayerId = -1;

	Terrain* terrain;
	float camera_distance;
	bool wasMouseDown;

	Client* client;
	std::thread clientThread;

	std::hash_map<int, Entity*> entities;

	void Update(float delta);
	void HandlePacket(ENetPacket* packet);

	template<typename T>
	T PacketToMessage(ENetPacket* packet);

	/* Initiliaztion */
	void LocateResources();
	void SetupPlugins();
	void SetupRenderer();
	void SetupWindow();
	void SetupViewport();
	void SetupInput();


	/* Events */
	void HandleConnectResponseMessage(const mosp::ConnectResponseMessage& message);
	void HandlePlayerConnectMessage(const mosp::PlayerConnectMessage& message);
	void HandlePlayerMovedMessage(const mosp::PlayerMovedMessage& message);
};

