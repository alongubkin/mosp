#pragma once
#include "stdafx.h"
#include "Terrain.h"
#include "Player.h"
#include "OGRE/OgreCamera.h"

class Game
{
private:
	Ogre::Root* ogreRoot;
	Ogre::RenderWindow* window;
	Ogre::SceneManager* sceneManager;
	Ogre::Viewport* viewport;
	Ogre::Camera* camera;
	OIS::Keyboard* keyboard;
	OIS::Mouse* mouse;

	Terrain* terrain;
	Player* player;

public:
	Game(Ogre::Root* ogreRoot, Ogre::RenderWindow* window, Ogre::SceneManager* sceneManager, Ogre::Viewport* viewport, Ogre::Camera* camera, OIS::Keyboard* keyboard, OIS::Mouse* mouse);
	~Game();
	void Update(float delta);
};

