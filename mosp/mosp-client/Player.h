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

	Ogre::AnimationState* animationTop;
	Ogre::AnimationState* animationBase;

	Player(Ogre::SceneManager* sceneManager);
	~Player();
	void SetTarget(float x, float y);
	void Update(float delta);
};

