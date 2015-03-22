#include "EventHandler.h"
#include "GameObject.h"
#include "InputManager.h"

#ifndef __FrameEvent_h__
#define __FrameEvent_h__

/*struct FrameEvent
     {
         float timeSinceLastEvent;
         float timeSinceLastFrame;
     };
*/// Ogre stuff in case we want to implement
using std::vector;


class FrameListener{
private:
	EventHandler* ev;
	InputManager* m_im;
	vector<GameObject*> vector_of_game_object;//list containing all the game objects connected with this frame listener
public:
	#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX FrameListener included")
	FrameListener(EventHandler*,InputManager*);
	virtual bool frameStarted()
	{return true;}
	virtual bool frameEnded()
	{return true;}
	void addUpdatableObject(GameObject* game_obj);
	void removeObject(GameObject* game_obj);
	void notifyObjects();
	/*
		call all the events for see if there are some new events to take care
	*/
	bool getEvents();
};

#endif