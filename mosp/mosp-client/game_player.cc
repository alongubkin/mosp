#include "stdafx.h"
#include "game_player.h"
#include "Game.h"
#include "proto/messages.pb.h"

GamePlayer::GamePlayer(Game* game, Ogre::SceneManager* sceneManager)
: Player(game, sceneManager)
{
}


GamePlayer::~GamePlayer()
{
	Player::~Player();
}

void GamePlayer::SetTarget(float x, float y)
{
	Player::SetTarget(x, y);

	mosp::Vector2 *position = new mosp::Vector2();
	position->set_x(x);
	position->set_y(y);

	game->GetNetworkManager()->UpdateTargetPosition(x, y);
}