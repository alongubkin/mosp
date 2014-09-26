#include "stdafx.h"
#include "Player.h"
#include "OGRE/OgreSkeleton.h"
#include "Game.h"
#include "proto/messages.pb.h"

Player::Player(Game* game, Ogre::SceneManager* sceneManager) 
	: Entity(game, sceneManager, "Sinbad.mesh")
{
	animationManager = new AnimationManager(entity);
	animationManager->SetAnimation("IdleBase");
	animationManager->SetAnimation("IdleTop");
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

	
	// this->game->GetClient()->Send();
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