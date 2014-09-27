#include "stdafx.h"
#include "controller_player.h"
#include "OGRE/OgreSkeleton.h"
#include "game.h"
#include "proto/messages.pb.h"
#include "movable_text.h"
#include "player.h"

ControllerPlayer::ControllerPlayer(Game* game, Ogre::SceneManager* sceneManager, std::string name)
	: Player(game, sceneManager, name)
{

}

void ControllerPlayer::SetTarget(float x, float y)
{
	Player::SetTarget(x, y);
	
	mosp::Vector2 *position = new mosp::Vector2();
	position->set_x(x);
	position->set_y(y);

	mosp::PlayerMovedMessage message;
	message.set_type(mosp::Type::PlayerMoved);
	message.set_allocated_position(position);
	message.set_client_id(0); // The server ignores this value

	this->game->GetClient()->Send(message);
}