#pragma once
#include "entity.h"

class Creature :
	public Entity
{
protected:
	Entity* follow;
public:
	Creature(Game* game, Ogre::SceneManager* sceneManager);
	~Creature();
	void SetEntityTarget(Entity* entity);
	void Update(float delta);
};

