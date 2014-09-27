#pragma once
#include "animation_manager.h"
#include "entity.h"

class Player : public Entity
{
public:
	AnimationManager* animationManager;

	Player(Game* game, Ogre::SceneManager* sceneManager);
	~Player();
	void SetTarget(float x, float y);
	void Update(float delta);
	void OnReachingTarget();
};

