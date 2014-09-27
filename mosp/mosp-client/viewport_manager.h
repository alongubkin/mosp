#ifndef _VIEWPORT_MANAGER_H
#define _VIEWPORT_MANAGER_H

#include "stdafx.h"

class Game;

class ViewportManager
{
public:
	ViewportManager(Game* game);
	~ViewportManager();

	void Initialize();
	void Update();
	void Close();

	Ogre::Camera* GetCamera() const { return _camera; }

	int GetActualWidth() const { return _viewport->getActualWidth(); }
	int GetActualHeight() const { return _viewport->getActualHeight(); }

	void SetCameraDistance(float cameraDistance) { _cameraDistance = cameraDistance; }

private:
	Game* _game;

	float _cameraDistance = 40.0f;

	Ogre::Viewport* _viewport;
	Ogre::Camera* _camera;
};

#endif