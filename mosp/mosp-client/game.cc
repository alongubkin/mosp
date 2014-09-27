#include "stdafx.h"
#include "game.h"


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

	SetupViewport();
	SetupInput();

	Ogre::Light* light = sceneManager->createLight("MainLight");
	light->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
	light->setDirection(1.0f, -5.0f, 3.0f);

	printf("============== Init Stats ==============\n");
	printf("Init Time: %f seconds.\n", initTimer->getMilliseconds() * 0.001f);
	printf("========================================\n");
	delete initTimer;

	/* Game engine intiliaztion */
	terrain = new Terrain(sceneManager);
	camera_distance = 40.0f;
	wasMouseDown = false;

	networkManager = new NetworkManager(this);
}


Game::~Game()
{
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

	delete networkManager;
}

void Game::Run()
{
	networkManager->Initialize();

	Ogre::Timer* timer = ogreRoot->getTimer();
	timer->reset();
	unsigned long lastFrame = timer->getMilliseconds();

	while (!window->isClosed() && !keyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		float delta = 0.001f * (timer->getMilliseconds() - lastFrame);
		lastFrame = timer->getMilliseconds();

		mouse->capture();
		keyboard->capture();

		Update(delta);

		window->update(true);
		ogreRoot->renderOneFrame();
		Ogre::WindowEventUtilities::messagePump();
	}

	networkManager->Close();
}


void Game::Update(float delta)
{
	Entity* player = GetEntity(networkManager->GetCurrentClientId());
	if (player != nullptr)
	{
		camera->setPosition(player->getPos() + Ogre::Vector3(0, camera_distance, camera_distance));
		camera->lookAt(player->getPos());
	}


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

	if (!wasMouseDown && mouseState.buttonDown(OIS::MouseButtonID::MB_Left))
	{
		Ogre::Ray mouseRay = camera->getCameraToViewportRay(mouseState.X.abs / (Ogre::Real) mouseState.width, mouseState.Y.abs / (Ogre::Real) mouseState.height);
		std::pair<bool, Ogre::Real> floorPoint = mouseRay.intersects(Ogre::Plane(Ogre::Vector3::UNIT_Y, 0));
		if (floorPoint.first) {
			Ogre::Vector3 point = mouseRay.getPoint(floorPoint.second);
			player->SetTarget(point.x, point.z);
		}
	}

	networkManager->Update();

	wasMouseDown = mouseState.buttonDown(OIS::MouseButtonID::MB_Left);

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

void Game::SetupViewport()
{
	camera = sceneManager->createCamera("MainCamera");
	sceneManager->getRootSceneNode()->createChildSceneNode("CameraNode")->attachObject(camera);

	viewport = window->addViewport(camera, 100, 0, 0, 1.0f, 1.0f);
	viewport->setAutoUpdated(true);
	viewport->setBackgroundColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	camera->setAspectRatio(viewport->getActualWidth() / (float)viewport->getActualHeight());
	camera->setNearClipDistance(0.5f);
	camera->setFarClipDistance(1000.0f);
}

void Game::SetupInput()
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