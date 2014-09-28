#include "stdafx.h"
#include "game.h"
#include "config.h"

Game::Game()
{
	/* OGRE3D Engine initiliaztion */
	Ogre::Timer* initTimer = new Ogre::Timer();
	initTimer->reset();

	ogreRoot = new Ogre::Root();

	SetupPlugins();
	SetupRenderer();
	ogreRoot->initialise(false);
	SetupWindow();

	sceneManager = ogreRoot->createSceneManager(Ogre::ST_GENERIC);
	sceneManager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
	sceneManager->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

	Ogre::OverlaySystem* pOverlaySystem = new Ogre::OverlaySystem();
	sceneManager->addRenderQueueListener(pOverlaySystem);

	LocateResources();
	
	Config::Load();
	networkManager = new NetworkManager(this);
	viewportManager = new ViewportManager(this);
	inputManager = new InputManager(this);
}


Game::~Game()
{
	
	sceneManager->destroyAllManualObjects();
	sceneManager->destroyAllEntities();
	sceneManager->getRootSceneNode()->removeAndDestroyAllChildren();
	Ogre::LogManager::getSingleton().logMessage("end of the program");

	delete inputManager; 
	inputManager = nullptr;

	delete viewportManager; 
	viewportManager = nullptr;

	delete networkManager;
	networkManager = nullptr;
}

void Game::Run()
{
	networkManager->Initialize();
	viewportManager->Initialize();
	inputManager->Initialize();

	Ogre::Light* light = sceneManager->createLight("MainLight");
	light->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
	light->setDirection(1.0f, -5.0f, 3.0f);

	/* Game engine intiliaztion */
	terrain = new Terrain(sceneManager);

	Ogre::Timer* timer = ogreRoot->getTimer();
	timer->reset();
	unsigned long lastFrame = timer->getMilliseconds();

	while (!window->isClosed()) // && !keyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		float delta = 0.001f * (timer->getMilliseconds() - lastFrame);
		lastFrame = timer->getMilliseconds();

		Update(delta);

		window->update(true);
		ogreRoot->renderOneFrame();
		Ogre::WindowEventUtilities::messagePump();
	}

	inputManager->Close();
	viewportManager->Close();
	networkManager->Close();
}


void Game::Update(float delta)
{
	viewportManager->Update();
	networkManager->Update();
	inputManager->Update();	

	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		(*it).second->Update(delta);
	}
}

void Game::SetEntity(int id, Entity* entity)
{
	entities[id] = entity;
}

Entity* Game::GetEntity(int id)
{
	if (!entities.count(id))
		return nullptr;

	return entities[id];
}

ControllerPlayer* Game::GetControllerPlayer()
{
	return static_cast<ControllerPlayer*>(GetEntity(networkManager->GetCurrentClientId()));
}

void Game::LocateResources()
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

void Game::SetupPlugins()
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

void Game::SetupRenderer()
{
	const Ogre::RenderSystemList& availableRenderers = ogreRoot->getAvailableRenderers();
	if (availableRenderers.size() == 0)
	{
		Ogre::LogManager::getSingleton().logMessage("Sorry, No rendersystem was found.");
	}
	ogreRoot->setRenderSystem(availableRenderers[0]);
}

void Game::SetupWindow()
{
	window = ogreRoot->createRenderWindow("Ogre Test", 640, 480, false);
	window->setVSyncEnabled(true);
	window->setActive(true);
	window->setAutoUpdated(false);
	ogreRoot->clearEventTimes();
}