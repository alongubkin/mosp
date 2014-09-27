#include "stdafx.h"
#include "controller_player.h"
#include "OGRE/OgreSkeleton.h"
#include "game.h"
#include "proto/messages.pb.h"
#include "movable_text.h"
#include "player.h"

ControllerPlayer::ControllerPlayer(Game* game, std::string name)
	: Player(game, name)
{

}

void ControllerPlayer::SetTarget(float x, float y)
{
	Player::SetTarget(x, y);
	game->GetNetworkManager()->UpdateTargetPosition(x, y);
}