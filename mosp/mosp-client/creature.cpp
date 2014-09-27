#include "stdafx.h"
#include "creature.h"


Creature::Creature(Game* game, Ogre::SceneManager* sceneManager)
: Entity(game, "Sinbad.mesh")
{
	follow = nullptr;
	MOVE_SPEED = 10.0f;
}


Creature::~Creature()
{
	Entity::~Entity();
}

void Creature::SetEntityTarget(Entity* entity)
{
	follow = entity;
}

void Creature::Update(float delta)
{
	Entity::Update(delta);

	if (follow != nullptr && target != follow->getPos2D())
	{
		SetTarget(follow->getPos2D().x, follow->getPos2D().y);
	}
}
