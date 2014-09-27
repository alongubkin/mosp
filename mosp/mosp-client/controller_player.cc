#include "stdafx.h"
#include "controller_player.h"
#include "OGRE/OgreSkeleton.h"
#include "game.h"
#include "proto/messages.pb.h"
#include "movable_text.h"

ControllerPlayer::ControllerPlayer(Game* game, Ogre::SceneManager* sceneManager)
	: Entity(game, sceneManager, "Sinbad.mesh")
{
	animationManager = new AnimationManager(entity);
	animationManager->SetAnimation("IdleBase");
	animationManager->SetAnimation("IdleTop");
}


ControllerPlayer::~ControllerPlayer()
{
	Entity::~Entity();
}

void ControllerPlayer::SetTarget(float x, float y)
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

void ControllerPlayer::Update(float delta)
{
	Entity::Update(delta);
	animationManager->Update(delta);
}

void ControllerPlayer::OnReachingTarget()
{
	Entity::OnReachingTarget();
	animationManager->SetAnimation("IdleBase", "RunBase");
	animationManager->SetAnimation("IdleTop", "RunTop");
}