#include "FrameListener.h"

FrameListener::FrameListener(EventHandler* e, InputManager* im){
	m_im=im;
	ev=e;
}

void FrameListener::addUpdatableObject(GameObject* game_obj){

	vector_of_game_object.push_back(game_obj);//add the gameobject to the end of the list 
}

void FrameListener::removeObject(GameObject* game_obj){

	vector_of_game_object.erase(vector_of_game_object.begin());//add the gameobject to the end of the list 
}

void FrameListener::notifyObjects()
{
	/*
	vector<GameObject*>::iterator i;
	EventHandler eh;

		for(i=vector_of_game_object.begin(); i!=vector_of_game_object.end();i++){//for every object
			(*i)->update(ev->returnVectorOfEvents());
		}
	*/
}

bool FrameListener::getEvents(){

	if(m_im->QUIT)//the user press esc so he wwants to exit the program
			return false;
	
	/*
	 update the times of the events 
	
	*/
	ev->updateEvent();

	/*
		call all the events
	*/
	ev->addEvents(m_im->get_input_events());
	
	//notify the objects with the events
	notifyObjects();
	return true;//if i don't want to exit the program
}