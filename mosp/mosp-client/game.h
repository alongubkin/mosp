#pragma once
#include "stdafx.h"
#include <thread>
#include <hash_map>
#include "enet/enet.h"
#include "terrain.h"
#include "entity.h"
#include "network_manager.h"

class Game
{

public:
	Game();
	~Game();

	void Run();
	
	Ogre::SceneManager* GetSceneManager() const { return sceneManager; }

	NetworkManager* GetNetworkManager() const { return networkManager; }

	void SetEntity(int id, Entity* entity);
	Entity* GetEntity(int id);

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
	float camera_distance;
	bool wasMouseDown;

	std::hash_map<int, Entity*> entities;

	void Update(float delta);

	/* Initiliaztion */
	void LocateResources();
	void SetupPlugins();
	void SetupRenderer();
	void SetupWindow();
	void SetupViewport();
	void SetupInput();

	NetworkManager* networkManager;
};

