#pragma once
#include "AnimationManager.h"
#include "Entity.h"

class Player : public Entity
{
public:
	AnimationManager* animationManager;

	Player(Ogre::SceneManager* sceneManager);
	~Player();
	void SetTarget(float x, float y);
	void Update(float delta);
	void OnReachingTarget();
};

