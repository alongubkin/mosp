#include "stdafx.h"
#include "MPPlayer.h"
#include "OGRE/OgreSkeleton.h"
#include "Game.h"
#include "proto/messages.pb.h"
#include "MovableText.h"

MPPlayer::MPPlayer(Game* game, Ogre::SceneManager* sceneManager, const std::string& name)
: Entity(game, sceneManager, "Sinbad.mesh")
{
	this->name = name;

	animationManager = new AnimationManager(entity);
	animationManager->SetAnimation("IdleBase");
	animationManager->SetAnimation("IdleTop");

	Ogre::Vector3 *translate = new Ogre::Vector3(0.0f, 5.0f, 0.0f);
	Ogre::SceneNode* nameContainerNode = node->createChildSceneNode(*translate);

	Ogre::MovableText* nameNode = new Ogre::MovableText("TXT_001", name);
	nameNode->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_ABOVE);

	nameContainerNode->attachObject(nameNode);

}


MPPlayer::~MPPlayer()
{
	Entity::~Entity();
}

void MPPlayer::SetTarget(float x, float y)
{
	Entity::SetTarget(x, y);
	animationManager->SetAnimation("RunBase", "IdleBase");
	animationManager->SetAnimation("RunTop", "IdleTop");
}

void MPPlayer::Update(float delta)
{
	Entity::Update(delta);
	animationManager->Update(delta);
}

void MPPlayer::OnReachingTarget()
{
	Entity::OnReachingTarget();
	animationManager->SetAnimation("IdleBase", "RunBase");
	animationManager->SetAnimation("IdleTop", "RunTop");
}