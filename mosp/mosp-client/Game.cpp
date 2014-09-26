#include "stdafx.h"
#include "Game.h"


Game::Game(Ogre::Root* ogreRoot, Ogre::RenderWindow* window, Ogre::SceneManager* sceneManager, Ogre::Viewport* viewport, Ogre::Camera* camera, OIS::Keyboard* keyboard, OIS::Mouse* mouse)
{
	this->ogreRoot = ogreRoot;
	this->window = window;
	this->sceneManager = sceneManager;
	this->viewport = viewport;
	this->camera = camera;
	this->keyboard = keyboard;
	this->mouse = mouse;

	terrain = new Terrain(sceneManager);
	player = new Player(sceneManager);
	camera_distance = 40.0f;
}


Game::~Game()
{
}

void Game::Update(float delta)
{
	camera->setPosition(player->getPos() + Ogre::Vector3(0, camera_distance, camera_distance));
	camera->lookAt(player->getPos());

	Ogre::Vector3 movement = Ogre::Vector3::ZERO;
	if (keyboard->isKeyDown(OIS::KC_W))
	{
		movement.z += -1;
	}
	if (keyboard->isKeyDown(OIS::KC_S))
	{
		movement.z += 1;
	}
	if (keyboard->isKeyDown(OIS::KC_A))
	{
		movement.x += -1;
	}
	if (keyboard->isKeyDown(OIS::KC_D))
	{
		movement.x += 1;
	}
	movement.normalise();
	
	if (movement != Ogre::Vector3::ZERO)
		player->SetTarget(player->getPos().x + movement.x, player->getPos().z + movement.z);

	OIS::MouseState mouseState = mouse->getMouseState();
	if (mouseState.Z.rel)
		camera_distance -= mouseState.Z.rel / 20.0f;
	if (mouseState.buttonDown(OIS::MouseButtonID::MB_Left))
	{
		Ogre::Ray mouseRay = camera->getCameraToViewportRay(mouseState.X.abs / (Ogre::Real) mouseState.width, mouseState.Y.abs / (Ogre::Real) mouseState.height);
		std::pair<bool, Ogre::Real> floorPoint = mouseRay.intersects(Ogre::Plane(Ogre::Vector3::UNIT_Y, 0));
		if (floorPoint.first) {
			Ogre::Vector3 point = mouseRay.getPoint(floorPoint.second);
			player->SetTarget(point.x, point.z);
		}
	}
	player->Update(delta);
}