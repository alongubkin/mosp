#pragma once
#include "AnimationManager.h"
#include "Entity.h"

class MPPlayer : public Entity
{
private:
	std::string name;

public:
	AnimationManager* animationManager;

	MPPlayer(Game* game, Ogre::SceneManager* sceneManager, const std::string& name);
	~MPPlayer();

	void SetTarget(float x, float y);
	void Update(float delta);
	void OnReachingTarget();
};

