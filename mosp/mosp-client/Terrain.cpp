#include "stdafx.h"
#include "Terrain.h"

Terrain::Terrain(Ogre::SceneManager* sceneManager)
{
	Ogre::MeshManager::getSingleton().createPlane("floor", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 450.0f, 450.0f, 10, 10, true, 1, 10.0f, 10.0f, Ogre::Vector3::UNIT_X);
	Ogre::Entity* planeEnt = sceneManager->createEntity("plane", "floor");
	planeEnt->setMaterialName("Examples/GrassFloor");
	planeEnt->setCastShadows(false);
	sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(planeEnt);
}


Terrain::~Terrain()
{


}
