#pragma once
#include "stdafx.h"
#include "Game.h"

int main()
{
	enet_initialize();

	Game game;
	game.Run();

	enet_deinitialize();

	return 0;
}