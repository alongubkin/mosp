#include "input_manager.h"
#include "game.h"
#include "viewport_manager.h"

InputManager::InputManager(Game* game)
	: _game(game)
{
	size_t windowHandle = 0;
	_game->GetWindow()->getCustomAttribute("WINDOW", &windowHandle);

	std::string windowsHandleAsString = "";
	{
		std::ostringstream windowHndStr;
		windowHndStr << windowHandle;
		windowsHandleAsString = windowHndStr.str();
	}

	OIS::ParamList specialParameters;
	specialParameters.insert(std::make_pair(std::string("WINDOW"), windowsHandleAsString));
#if defined OIS_WIN32_PLATFORM
	specialParameters.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	specialParameters.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	specialParameters.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	specialParameters.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	specialParameters.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	specialParameters.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	specialParameters.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	specialParameters.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

	_input = OIS::InputManager::createInputSystem(specialParameters);
}

InputManager::~InputManager()
{
	OIS::InputManager::destroyInputSystem(_input);
	_input = nullptr;
}

void InputManager::Initialize()
{
	_mouse = static_cast<OIS::Mouse*>(_input->createInputObject(OIS::OISMouse, true));
	_mouse->getMouseState().width = _game->GetViewportManager()->GetActualWidth();
	_mouse->getMouseState().height = _game->GetViewportManager()->GetActualHeight();

	_keyboard = static_cast<OIS::Keyboard*>(_input->createInputObject(OIS::OISKeyboard, false));
}

void InputManager::Update()
{
	_mouse->capture();
	_keyboard->capture();

	ControllerPlayer* player = _game->GetControllerPlayer();

	if (player != nullptr)
	{
		HandleKeyboardInput(player);
		HandleMouseInput(player);
	}
}

void InputManager::Close()
{
	_input->destroyInputObject(_keyboard);
	_input->destroyInputObject(_mouse);
	
	_keyboard = nullptr;
	_mouse = nullptr;
}

void InputManager::HandleKeyboardInput(ControllerPlayer* player)
{
	Ogre::Vector3 movement = Ogre::Vector3::ZERO;

	if (_keyboard->isKeyDown(OIS::KC_W))
	{
		movement.z += -1;
	}

	if (_keyboard->isKeyDown(OIS::KC_S))
	{
		movement.z += 1;
	}

	if (_keyboard->isKeyDown(OIS::KC_A))
	{
		movement.x += -1;
	}

	if (_keyboard->isKeyDown(OIS::KC_D))
	{
		movement.x += 1;
	}

	movement.normalise();

	if (movement != Ogre::Vector3::ZERO)
	{
		//(movement * 10) % 5
		player->SetTarget(player->getPos().x + movement.x, player->getPos().z + movement.z);
	}
}

void InputManager::HandleMouseInput(ControllerPlayer* player)
{
	OIS::MouseState mouseState = _mouse->getMouseState();
	if (mouseState.Z.rel)
		_game->GetViewportManager()->SetCameraDistance(mouseState.Z.rel / 20.0f);

	if (!_wasMouseDown && mouseState.buttonDown(OIS::MouseButtonID::MB_Left))
	{
		Ogre::Ray mouseRay = _game->GetViewportManager()->GetCamera()
			->getCameraToViewportRay(mouseState.X.abs / (Ogre::Real) mouseState.width, mouseState.Y.abs / (Ogre::Real) mouseState.height);
		std::pair<bool, Ogre::Real> floorPoint = mouseRay.intersects(Ogre::Plane(Ogre::Vector3::UNIT_Y, 0));
		if (floorPoint.first) 
		{
			Ogre::Vector3 point = mouseRay.getPoint(floorPoint.second);
			player->SetTarget(point.x, point.z);
		}
	}

	_wasMouseDown = mouseState.buttonDown(OIS::MouseButtonID::MB_Left);
}

bool InputManager::isKeyDown(OIS::KeyCode key)
{
	return _keyboard->isKeyDown(key);
}