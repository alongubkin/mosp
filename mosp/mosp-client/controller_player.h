#pragma once
#include "animation_manager.h"
#include "player.h"

class ControllerPlayer : public Player
{
public:
	ControllerPlayer(Game* game, std::string name);
	void SetTarget(float x, float y);
};

