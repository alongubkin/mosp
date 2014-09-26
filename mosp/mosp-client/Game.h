#pragma once
#include "stdafx.h"
#include "enet/enet.h"
#include "Terrain.h"
#include "Player.h"
#include "Client.h"

class Game
{

public:
	Game();
	~Game();

	void Run();
	
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

	Client client;
	std::thread clientThread;

	void Update(float delta);

	template<typename T>
	T PacketToMessage(ENetPacket* packet);

	/* Initiliaztion */
	void LocateResources();
	void SetupPlugins();
	void SetupRenderer();
	void SetupWindow();
	void SetupViewport();
	void SetupInput();
};

