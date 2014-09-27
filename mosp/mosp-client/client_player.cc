#include "stdafx.h"
#include "client_player.h"
#include "OGRE/OgreSkeleton.h"
#include "Game.h"
#include "proto/messages.pb.h"
#include "movable_text.h"

ClientPlayer::ClientPlayer(Game* game, const std::string& name)
: Player(game, game->GetSceneManager())
{
	this->name = name;
	Ogre::SceneNode* nameContainerNode = node->createChildSceneNode(Ogre::Vector3(0.0f, 5.0f, 0.0f));
	Ogre::MovableText* nameNode = new Ogre::MovableText(name, name, "ArialBold", 1.5f);
	nameNode->setTextAlignment(Ogre::MovableText::H_CENTER, Ogre::MovableText::V_ABOVE);
	nameContainerNode->attachObject(nameNode);

}

ClientPlayer::~ClientPlayer()
{
	Player::~Player();
}

void ClientPlayer::SetTarget(float x, float y)
{
	Player::SetTarget(x, y);
}

void ClientPlayer::Update(float delta)
{
	Player::Update(delta);
}

void ClientPlayer::OnReachingTarget()
{
	Player::OnReachingTarget();
}