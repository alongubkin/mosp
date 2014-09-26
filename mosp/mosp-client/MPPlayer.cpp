#include "stdafx.h"
#include "MPPlayer.h"
#include "OGRE/OgreSkeleton.h"
#include "Game.h"
#include "proto/messages.pb.h"

MPPlayer::MPPlayer(Game* game, Ogre::SceneManager* sceneManager)
: Entity(game, sceneManager, "Sinbad.mesh")
{
	animationManager = new AnimationManager(entity);
	animationManager->SetAnimation("IdleBase");
	animationManager->SetAnimation("IdleTop");
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