#include "stdafx.h"
#include "Player.h"
#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreBlendMode.h"
#include "OGRE/OgreSkeleton.h"
#include "OGRE/OgreSkeletonInstance.h"
#include "OGRE\OgreShadowVolumeExtrudeProgram.h"

Player::Player(Ogre::SceneManager* sceneManager)
{
	ogreNode = sceneManager->getRootSceneNode()->createChildSceneNode("OgreNode", Ogre::Vector3::UNIT_Y * 5.0f);

	ogre = sceneManager->createEntity("Ogre", "Sinbad.mesh");
	ogreNode->attachObject(ogre);

	animationManager = new AnimationManager(ogre);

	ogre->getSkeleton()->setBlendMode(Ogre::SkeletonAnimationBlendMode::ANIMBLEND_CUMULATIVE);
	animationManager->SetAnimation("IdleBase");
	animationManager->SetAnimation("IdleTop");

	target = Ogre::Vector3::ZERO;
}


Player::~Player()
{
}

void Player::SetTarget(float x, float y)
{
	target.x = x;
	target.z = y;
	target.y = ogreNode->getPosition().y;

	animationManager->SetAnimation("RunBase", "IdleBase");
	animationManager->SetAnimation("RunTop", "IdleTop");
}

void Player::Update(float delta)
{
	animationManager->Update(delta);

	float MOVE_SPEED = 20.0f;
	Ogre::Vector3 pos = ogreNode->getPosition();

	if (target.x == 0 && target.z == 0)
		return;

	Ogre::Vector3 dir = target - ogreNode->getPosition();
	dir.normalise();

	Ogre::Vector3 src = ogreNode->getOrientation() * Ogre::Vector3::UNIT_Z;
	Ogre::Quaternion quat = src.getRotationTo(dir, Ogre::Vector3::UNIT_Y);
	quat.x = 0;
	quat.z = 0;
	ogreNode->rotate(quat);

	if (pos.squaredDistance(target) <= (dir * delta * MOVE_SPEED).squaredLength()) {
		ogreNode->setPosition(target);
		target.x = 0;
		target.z = 0;
		animationManager->SetAnimation("IdleBase", "RunBase");
		animationManager->SetAnimation("IdleTop", "RunTop");
	}
	else
		ogreNode->translate(dir * delta * MOVE_SPEED);
}
