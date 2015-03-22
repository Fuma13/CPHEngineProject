#ifndef GameLoop_H
#define GameLoop_H

#pragma once
#include "MemoryManager.h"
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include <list>
#include <vector>
using namespace std;

class Event;

class GameLoop
{
private:
	vector<Event*> input_events;
	bool gameLoop();
	//For FPS calculation
	Uint32 startclock;
	Uint32 deltaclock;
	Uint32 currentFPS;
	int TICKS_PER_SECOND;
	int SKIP_TICKS;
	int TICKS_FOR_SECOND_AI;
	int SKIP_TICKS_AI;
	int MAX_FRAMESKIP;
	DWORD next_game_tick;
	DWORD next_game_tick_ai;
	static GameLoop* game_loop;
	void callGameLoop(bool,const int base_fps,const int low_fps);
public:

	/*	@Param base_fps: how many fps you want
		@Param low_fps: minimum fps for having game logic at base fps speed
	*/
	static GameLoop* getInstance();
	
	/*
		i set the game_is:run variable so i know if the game loop have to start or not.
		after i call the method for call the game loop with the right parameters		
	*/
	void startEngine(bool,const int base_fps,const int low_fps);
};

#endif