#pragma once
#include "stdafx.h"
#include <map>
#include <vector>

class AnimationManager
{
private:
	std::map<Ogre::String, Ogre::AnimationState*> animations;
	std::vector<Ogre::AnimationState*> fadeIn;
	std::vector<Ogre::AnimationState*> fadeOut;
public:
	AnimationManager(Ogre::Entity* entity)
	{
		Ogre::AnimationStateIterator it = entity->getAllAnimationStates()->getAnimationStateIterator();
		it.begin();
		while (it.hasMoreElements())
		{
			Ogre::AnimationState* anim = it.current()->second;
			Ogre::String name = it.current()->first;

			animations.insert(std::make_pair(name, anim));

			it.moveNext();
		}
	}

	~AnimationManager()
	{
	}

	void SetAnimation(Ogre::String name, Ogre::String cancel = "", bool loop = true)
	{
		Ogre::AnimationState* anim = animations[name];
		anim->setEnabled(true);
		anim->setLoop(loop);
		anim->setWeight(1.0);
		fadeIn.push_back(anim);
		if (cancel != "")
		{
			animations[cancel]->setEnabled(false);
		}
	}

	void Update(float delta)
	{
		for (std::map<Ogre::String, Ogre::AnimationState*>::iterator it = animations.begin(); it != animations.end(); it++)
		{
			if ((*it).second->getEnabled())
				(*it).second->addTime(delta);
		}
		/*for (std::vector<Ogre::AnimationState*>::iterator it = fadeIn.begin(); it != fadeIn.end(); it++)
		{
		float w = (*it)->getWeight();
		if (w >= 1.0f)
		{

		}
		else
		{
		(*it)->setWeight(w + 0.01f);
		}


		}*/
	}
};

