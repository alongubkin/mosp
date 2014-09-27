#pragma once
#include "animation_manager.h"
#include "entity.h"

class Player : public Entity
{
private:
	std::string name;

public:
	AnimationManager* animationManager;

	Player(Game* game, Ogre::SceneManager* sceneManager, const std::string& name);
	~Player();

	void SetTarget(float x, float y);
	void Update(float delta);
	void OnReachingTarget();
};

