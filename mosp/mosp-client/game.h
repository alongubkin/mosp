#pragma once
#include "stdafx.h"
#include <thread>
#include <hash_map>
#include "enet/enet.h"
#include "terrain.h"
#include "entity.h"
#include "controller_player.h"

#include "network_manager.h"
#include "viewport_manager.h"


class Game
{

public:
	Game();
	~Game();

	void Run();
	
	Ogre::SceneManager* GetSceneManager() const { return sceneManager; }
	Ogre::RenderWindow* GetWindow() const { return window; }

	NetworkManager* GetNetworkManager() const { return networkManager; }
	ViewportManager* GetViewportManager() const { return viewportManager; }

	void SetEntity(int id, Entity* entity);
	Entity* GetEntity(int id);
	ControllerPlayer* GetControllerPlayer();

private:
	Ogre::Root* ogreRoot;
	Ogre::RenderWindow* window;
	Ogre::SceneManager* sceneManager;
	
	OIS::InputManager* inputManager;
	OIS::Keyboard* keyboard;
	OIS::Mouse* mouse;

	Terrain* terrain;
	
	bool wasMouseDown;

	std::hash_map<int, Entity*> entities;

	void Update(float delta);

	/* Initiliaztion */
	void LocateResources();
	void SetupPlugins();
	void SetupRenderer();
	void SetupWindow();
	void SetupInput();

	NetworkManager* networkManager;
	ViewportManager* viewportManager;
};

