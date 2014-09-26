#pragma once
#include "AnimationManager.h"

class Game;

class Entity
{
protected:
	Game* game;
	Ogre::SceneNode* node;
	Ogre::Entity* entity;
	Ogre::Vector2 target;
	float MOVE_SPEED;

public:
	Entity(Game *game, Ogre::SceneManager* sceneManager, Ogre::String meshName);
	~Entity();
	virtual void SetTarget(float x, float y);
	virtual void Update(float delta);
	Ogre::Vector3 getPos() { return node->getPosition(); };
	Ogre::Vector2 getPos2D() { return Ogre::Vector2(node->getPosition().x, node->getPosition().z); };
	virtual void OnReachingTarget();
};

