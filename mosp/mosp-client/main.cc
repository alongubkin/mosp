#pragma once
#include "stdafx.h"
#include "game.h"

int main()
{
	enet_initialize();

	Game game;
	game.Run();

	enet_deinitialize();

	return 0;
}