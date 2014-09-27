#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#include "game_player.h"

class Game;

class InputManager
{
public:
	InputManager(Game* game);
	~InputManager();

	void Initialize();
	void Update();
	void Close();

private:
	Game* _game;

	bool _wasMouseDown = false;

	OIS::InputManager* _input;
	OIS::Keyboard* _keyboard;
	OIS::Mouse* _mouse;

	void HandleKeyboardInput(GamePlayer* player);
	void HandleMouseInput(GamePlayer* player);
};

#endif