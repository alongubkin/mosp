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

	mosp::Vector3 *position = new mosp::Vector3();
	position->set_x(x);
	position->set_y(y);
	position->set_z(0);

	mosp::MoveRequestMessage message;
	message.set_type(mosp::Type::MoveRequest);
	message.set_allocated_position(position);

	this->game->GetClient()->Send(message);
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