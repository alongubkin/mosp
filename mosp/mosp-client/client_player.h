#pragma once
#include "player.h"

class ClientPlayer : public Player
{
private:
	std::string name;

public:
	ClientPlayer(Game* game, const std::string& name);
	~ClientPlayer();

	void SetTarget(float x, float y);
	void Update(float delta);
	void OnReachingTarget();
};

