#include "stdafx.h"
#include "Player.h"
#include "OGRE/OgreSkeleton.h"
#include "Game.h"
#include "proto/messages.pb.h"
#include "MovableText.h"

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

	mosp::Vector2 *position = new mosp::Vector2();
	position->set_x(x);
	position->set_y(y);

	mosp::PlayerMovedMessage message;
	message.set_type(mosp::Type::PlayerMoved);
	message.set_allocated_position(position);
	message.set_client_id(0); // The server ignores this value

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