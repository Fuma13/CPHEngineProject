#ifndef __Event_h__
#define __Event_h__

#include "SDL.h"
#include "SDL_opengl.h"
#include <windows.h>
#include <ctime>
#include <vector>

class Event{//must be an interface for all the events

public:	
		clock_t cycles;//@ param number of clock ticks
		unsigned int start;
		unsigned int milliseconds;//@param  number of milliseconds
		clock_t tick;
		bool time;//variable use for unserstand if i use time or cycles of clock
		
		Event();
		Event(unsigned int time);
		Event(clock_t clo);
		/*
		@warning
			update the time of the object based
			on the ticks of the cpu clock
		*/
		virtual void updateCycles();
		/*
		@warning
			update the time of the object based
			on milliseconds	and return true when the time/cycles are euqal to zero	
		*/
		virtual void updateTime();
		virtual bool update();


    	
private:
		
};

#endif