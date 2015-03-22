#include "Event.h"

Event::Event(){

	cycles=0;
	milliseconds=1;
	time=true;
}

Event::Event(unsigned int value_of_time){

	milliseconds = value_of_time; 
	start=SDL_GetTicks();
	time=true;
}

Event::Event(clock_t clo){

	cycles=clo;
	tick = clock();
	time=false;
}

void Event::updateCycles(){

	cycles -= clock() - tick;
}

void Event::updateTime(){

	milliseconds -= SDL_GetTicks() - start;
}

bool Event::update(){

	if(time){
		
		updateTime();
	}else{

		updateCycles();	
	}
	if(milliseconds==0)
	{
		return true;
	}
	return false;
}



