#pragma once
#include "stdafx.h"
#include <thread>
#include <hash_map>
#include "enet/enet.h"
#include "Terrain.h"
#include "Player.h"
#include "Client.h"
#include "MPPlayer.h"
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

	Terrain* terrain;
	Player* player;
	float camera_distance;

	Client* client;
	std::thread clientThread;

	std::hash_map<int, MPPlayer*> players;

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
	void HandleJoinNotificationMessage(const mosp::JoinNotificationMessage& message);
	void HandleMoveNotificationMessage(const mosp::MoveNotificationMessage& message);
};

