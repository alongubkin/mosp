#pragma once
#include "animation_manager.h"
#include "entity.h"

class ControllerPlayer : public Entity
{
public:
	AnimationManager* animationManager;

	ControllerPlayer(Game* game, Ogre::SceneManager* sceneManager);
	~ControllerPlayer();
	void SetTarget(float x, float y);
	void Update(float delta);
	void OnReachingTarget();
};

