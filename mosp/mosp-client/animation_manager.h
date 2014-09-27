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
		if (anim->getEnabled())
			return;

		anim->setEnabled(true);
		anim->setLoop(loop);
		fadeIn.push_back(anim);
		if (cancel != "")
		{
			animations[cancel]->setEnabled(false);
			fadeOut.push_back(animations[cancel]);
		}
	}

	void Update(float delta)
	{
		for (std::map<Ogre::String, Ogre::AnimationState*>::iterator it = animations.begin(); it != animations.end(); it++)
		{
			if ((*it).second->getEnabled())
				(*it).second->addTime(delta);
		}
		/*std::vector<Ogre::AnimationState*> toberemoved;
		for (std::vector<Ogre::AnimationState*>::iterator it = fadeIn.begin(); it != fadeIn.end(); it++)
		{
			float w = (*it)->getWeight();
			if (w >= 1.0f)
			{
				(*it)->setWeight(1.0f);
				toberemoved.push_back(*it);
			}
			else
				(*it)->setWeight(w + delta);
		}
		for (std::vector<Ogre::AnimationState*>::iterator it = toberemoved.begin(); it != toberemoved.end(); it++)
			fadeIn.erase(std::remove(fadeIn.begin(), fadeIn.end(), (*it)), fadeIn.end());

		toberemoved.clear();
		for (std::vector<Ogre::AnimationState*>::iterator it = fadeOut.begin(); it != fadeOut.end(); it++)
		{
			float w = (*it)->getWeight();
			if (w <= 0.0f)
			{
				(*it)->setWeight(0.0f);
				toberemoved.push_back(*it);
			}
			else
				(*it)->setWeight(w - delta);
		}
		for (std::vector<Ogre::AnimationState*>::iterator it = toberemoved.begin(); it != toberemoved.end(); it++)
			fadeOut.erase(std::remove(fadeOut.begin(), fadeOut.end(), (*it)), fadeOut.end());
		*/
	}
};

