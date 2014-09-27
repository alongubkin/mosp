#pragma once
#include <iostream>
#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreEntity.h"
#include "OGRE/OgreConfigFile.h"
#include "OIS/OIS.h"
#include "OGRE/OgreMeshManager.h"
#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreLogManager.h"
#include "OGRE/OgreSceneManager.h"
#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreViewport.h"
#include "OGRE/OgreTimer.h"
#include "OGRE/OgreCamera.h"
#include "OGRE/OgreMovableObject.h"
#include "OGRE/Overlay/OgreOverlaySystem.h"
#include "OGRE/Overlay/OgreFont.h"
#include "OGRE/Overlay/OgreFontManager.h"
#include "OGRE/OgreMaterialManager.h"

// any other header can be included, as usual
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif