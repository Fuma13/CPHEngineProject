#include "EventHandler.h";

EventHandler::EventHandler(){

	std::vector <Event*>* vector_of_events = new std::vector <Event*>(1,nullptr);
}

EventHandler::~EventHandler(){

	delete[] vector_of_events;
}

void EventHandler::addEvents(std::vector<Event*> ev){
	
	vector_of_events->push_back(ev);
	
}

std::vector<std::vector<Event*>> * EventHandler::returnVectorOfEvents(){

	return &(*vector_of_events);
}
void EventHandler::updateEvent()
{

	std::vector <std::vector<Event*>>::iterator i;
	std::vector <Event*>::iterator m;

	for(i=vector_of_events->begin(); i<vector_of_events->end(); i++){
		for(m=i->begin(); m<i->end(); m++){
			if((*m)->update()){
				i->erase(m);
			}
		}
	}
}

