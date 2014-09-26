#pragma once
#include "AnimationManager.h"
#include "Entity.h"

class MPPlayer : public Entity
{
public:
	AnimationManager* animationManager;

	MPPlayer(Game* game, Ogre::SceneManager* sceneManager);
	~MPPlayer();
	void SetTarget(float x, float y);
	void Update(float delta);
	void OnReachingTarget();
};

