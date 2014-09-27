#include "stdafx.h"
#include "player.h"
#include "OGRE/OgreSkeleton.h"
#include "game.h"
#include "proto/messages.pb.h"
#include "movable_text.h"

Player::Player(Game* game, Ogre::SceneManager* sceneManager, const std::string& name)
: Entity(game, sceneManager, "Sinbad.mesh")
{
	this->name = name;

	animationManager = new AnimationManager(entity);
	animationManager->SetAnimation("IdleBase");
	animationManager->SetAnimation("IdleTop");

	Ogre::SceneNode* nameContainerNode = node->createChildSceneNode(Ogre::Vector3(0.0f, 5.0f, 0.0f));
	Ogre::MovableText* nameNode = new Ogre::MovableText(name, name, "ArialBold", 1.5f);
	nameNode->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_ABOVE);
	nameContainerNode->attachObject(nameNode);

}


Player::~Player()
{
	Entity::~Entity();
}

void Player::SetTarget(float x, float y)
{
	Entity::SetTarget(x, y);
	animationManager->SetAnimation("RunBase", "IdleBase");
	animationManager->SetAnimation("RunTop", "IdleTop");
}

void Player::Update(float delta)
{
	Entity::Update(delta);
	animationManager->Update(delta);
}

void Player::OnReachingTarget()
{
	Entity::OnReachingTarget();
	animationManager->SetAnimation("IdleBase", "RunBase");
	animationManager->SetAnimation("IdleTop", "RunTop");
}