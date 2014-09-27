#include "stdafx.h"
#include "Entity.h"


Entity::Entity(Game* game, Ogre::SceneManager* sceneManager, Ogre::String meshName)
{
	this->game = game;
	node = sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3::UNIT_Y * 5.0f);

	entity = sceneManager->createEntity(meshName);
	node->attachObject(entity);
	target = Ogre::Vector2::ZERO;
	MOVE_SPEED = 15.0f;
}


Entity::~Entity()
{
}

void Entity::SetTarget(float x, float y)
{
	target.x = x;
	target.y = y;
}

void Entity::Update(float delta)
{
	if (target == Ogre::Vector2::ZERO)
		return;

	Ogre::Vector2 dir = target - getPos2D();
	dir.normalise();

	Ogre::Vector3 src = node->getOrientation() * Ogre::Vector3::UNIT_Z;
	Ogre::Vector3 dir3 = Ogre::Vector3(dir.x, 0, dir.y);
	Ogre::Quaternion quat = src.getRotationTo(dir3, Ogre::Vector3::UNIT_Y);
	quat.x = 0;
	quat.z = 0;
	node->rotate(quat);

	if (getPos2D().squaredDistance(target) <= (dir * delta * MOVE_SPEED).squaredLength()) {
		node->setPosition(target.x, getPos().y, target.y);
		target.x = 0;
		target.y = 0;
		OnReachingTarget();
	}
	else
		node->translate(dir3 * delta * MOVE_SPEED);
}

void Entity::OnReachingTarget()
{

}

