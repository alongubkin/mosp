#pragma once
#include "stdafx.h"
#include <memory>
#include <exception>
#include "Game.h"
#include "OGRE/OgreLogManager.h"
#include "OGRE/OgreSceneManager.h"
#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreViewport.h"
#include "OGRE/OgreTimer.h"

Ogre::Root* ogreRoot;
Ogre::RenderWindow* window;
Ogre::SceneManager* sceneManager;
Ogre::Viewport* viewport;
Ogre::Camera* camera;
OIS::InputManager* inputManager;
OIS::Keyboard* keyboard;
OIS::Mouse* mouse;

void locateResources()
{
	// load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	Ogre::String sec, type, arch;

	// go through all specified resource groups
	while (seci.hasMoreElements())
	{
		sec = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		// go through all resource paths
		for (i = settings->begin(); i != settings->end(); i++)
		{
			type = i->first;
			arch = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void setupPlugins()
{
	std::vector<Ogre::String> pluginNames;
	pluginNames.push_back("RenderSystem_GL");
	pluginNames.push_back("Plugin_OctreeSceneManager");
	pluginNames.push_back("Plugin_CgProgramManager");

	for (std::vector<Ogre::String>::iterator iter = pluginNames.begin(); iter != pluginNames.end(); iter++)
	{
		Ogre::String &pluginName = *iter;
		if (OGRE_DEBUG_MODE)
		{
			pluginName.append("_d");
		}
		ogreRoot->loadPlugin(pluginName);
	}
}

void setupRenderer()
{
	const Ogre::RenderSystemList& availableRenderers = ogreRoot->getAvailableRenderers();
	if (availableRenderers.size() == 0)
	{
		Ogre::LogManager::getSingleton().logMessage("Sorry, No rendersystem was found.");
	}
	ogreRoot->setRenderSystem(availableRenderers[0]);
}

void setupWindow()
{
	window = ogreRoot->createRenderWindow("Ogre Test", 1280, 720, false);
	window->setVSyncEnabled(true);
	window->setActive(true);
	window->setAutoUpdated(false);
	ogreRoot->clearEventTimes();
}

void setupViewport()
{
	camera = sceneManager->createCamera("MainCamera");
	sceneManager->getRootSceneNode()->createChildSceneNode("CameraNode")->attachObject(camera);

	viewport = window->addViewport(camera, 100, 0, 0, 1.0f, 1.0f);
	viewport->setAutoUpdated(true);
	viewport->setBackgroundColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	camera->setAspectRatio(viewport->getActualWidth() / (float) viewport->getActualHeight());
	camera->setNearClipDistance(0.5f);
	camera->setFarClipDistance(1000.0f);
}

void setupInput()
{
	size_t windowHandle = 0;
	window->getCustomAttribute("WINDOW", &windowHandle);

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

	inputManager = OIS::InputManager::createInputSystem(specialParameters);

	mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));
	keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, false));
	mouse->getMouseState().width = viewport->getActualWidth();
	mouse->getMouseState().height = viewport->getActualHeight();
}


int main()
{
	try
	{
		ogreRoot = new Ogre::Root();

		setupPlugins();
		setupRenderer();
		ogreRoot->initialise(false);
		setupWindow();
		
		sceneManager = ogreRoot->createSceneManager(Ogre::ST_GENERIC);
		sceneManager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
		sceneManager->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
		
		locateResources();

		setupViewport();
		setupInput();
		
		Ogre::Light* light = sceneManager->createLight("MainLight");
		light->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
		light->setDirection(1.0f, -5.0f, 3.0f);

		Game* mainGame = new Game(ogreRoot, window, sceneManager, viewport, camera, keyboard, mouse);
		
		Ogre::Timer* timer = ogreRoot->getTimer();
		timer->reset();
		unsigned long lastFrame = timer->getMilliseconds();
		
		while (!window->isClosed() && !keyboard->isKeyDown(OIS::KC_ESCAPE))
		{
			float delta = 0.001f * (timer->getMilliseconds() - lastFrame);
			lastFrame = timer->getMilliseconds();

			mouse->capture();
			keyboard->capture();
			
			mainGame->Update(delta);
			
			window->update(false);
			window->swapBuffers();
			ogreRoot->renderOneFrame();
			Ogre::WindowEventUtilities::messagePump();
		}


		inputManager->destroyInputObject(keyboard);
		keyboard = nullptr;
		OIS::InputManager::destroyInputSystem(inputManager);
		inputManager = nullptr;
		window->removeAllViewports();
		sceneManager->destroyAllCameras();
		sceneManager->destroyAllManualObjects();
		sceneManager->destroyAllEntities();
		sceneManager->getRootSceneNode()->removeAndDestroyAllChildren();
		Ogre::LogManager::getSingleton().logMessage("end of the program");
	}
	catch (Ogre::Exception &e)
	{
		std::cout << "!!!!Ogre::Exception!!!!" << e.what() << std::endl;
		std::cin.get();
	}
	catch (std::exception &e)
	{
		std::cout << "!!!!std::exception!!!!" << e.what() << std::endl;
	}
	return 0;
}