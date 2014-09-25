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
}


Game::~Game()
{
}

void Game::Update(float delta)
{
	float RUN_SPEED = 50.0f;
	if (keyboard->isKeyDown(OIS::KC_W))
	{
		camera->setPosition(camera->getPosition() + Ogre::Vector3(0, 0, -RUN_SPEED) * delta);
	}
	if (keyboard->isKeyDown(OIS::KC_S))
	{
		camera->setPosition(camera->getPosition() + Ogre::Vector3(0, 0, RUN_SPEED) * delta);
	}
	if (keyboard->isKeyDown(OIS::KC_A))
	{
		camera->setPosition(camera->getPosition() + Ogre::Vector3(-RUN_SPEED, 0, 0) * delta);
	}
	if (keyboard->isKeyDown(OIS::KC_D))
	{
		camera->setPosition(camera->getPosition() + Ogre::Vector3(RUN_SPEED, 0, 0) * delta);
	}
	OIS::MouseState mouseState = mouse->getMouseState();
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