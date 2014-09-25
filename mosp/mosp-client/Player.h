#pragma once
#include "AnimationManager.h"

class Player
{
private:
	Ogre::Vector3 target;
	Ogre::Entity* ogre;
public:
	Ogre::SceneNode* ogreNode;
	AnimationManager* animationManager;

	Player(Ogre::SceneManager* sceneManager);
	~Player();
	void SetTarget(float x, float y);
	void Update(float delta);
};

