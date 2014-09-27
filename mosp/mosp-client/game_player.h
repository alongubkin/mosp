#pragma once
#include "player.h"

class GamePlayer : public Player
{
public:
	GamePlayer(Game* game, Ogre::SceneManager* sceneManager);
	~GamePlayer();
	void SetTarget(float x, float y);
};

