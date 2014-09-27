#include "viewport_manager.h"
#include "game.h"

void ViewportManager::Initialize()
{
	_camera = _game->GetSceneManager()->createCamera("MainCamera");
	_game->GetSceneManager()->getRootSceneNode()
		->createChildSceneNode("CameraNode")->attachObject(_camera);

	_viewport = _game->GetWindow()->addViewport(_camera, 100, 0, 0, 1.0f, 1.0f);
	_viewport->setAutoUpdated(true);
	_viewport->setBackgroundColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

	_camera->setAspectRatio(_viewport->getActualWidth() / (float)_viewport->getActualHeight());
	_camera->setNearClipDistance(0.5f);
	_camera->setFarClipDistance(1000.0f);
}

void ViewportManager::Update()
{
	ControllerPlayer* player = _game->GetControllerPlayer();

	if (player != nullptr)
	{
		_camera->setPosition(player->getPos() + Ogre::Vector3(0, _cameraDistance, _cameraDistance));
		_camera->lookAt(player->getPos());
	}
}

void ViewportManager::Close()
{
	_game->GetWindow()->removeAllViewports();
	_game->GetSceneManager()->destroyAllCameras();
}