#pragma once//include only one time on the compilation this file
#ifndef __EventHandler_h__
#define __EventHandler_h__
#include <vector>
#include "Event.h"
#include <typeinfo>

//FT: added gamePlay

class EventHandler{

public:
	const enum positions{Input,Ai,Physics,Sound, Gameplay};//positions in the vector
	EventHandler();
	~EventHandler();
	void addEvents(std::vector<Event*> ev);
	(std::vector <std::vector<Event*>>)* returnVectorOfEvents();
	/*
		update the TimeOfLife(tol) of all the events and, if the tol is euqal to zero
		delete them from the vector
	*/
	void updateEvent();

private:

	std::vector <std::vector<Event*>>* vector_of_events;//list containing all the events 

};
#endif