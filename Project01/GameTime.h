#ifndef __GameTime_h__
#define __GameTime_h__
#pragma once
#include "MemoryManager.h"
class GameTime
{
public:
	static GameTime * getInstance();

	#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX GameTime included")
	/*

	IDEAS FROM XNA

	// The amount of elapsed game time since the last update.
	// public TimeSpan ElapsedGameTime { get; set; }
	Uint32 get_elapsedGameTime();

	// Gets a value indicating that the game loop is taking longer than its TargetElapsedTime. In this case, the game loop can be considered to be running too slowly and should do something to "catch up."
	bool IsRunningSlowly();

	// The amount of game time since the start of the game.
	Uint32 TotalGameTime();
	*/


	// a counter for the number of game logic updates since the game started
	int get_totalUpdatesSinceStart();
	void increase_totalUpdatesSinceStart();
	
private:
	int totalUpdatesSinceStart;

	static GameTime* p_instance;
	~GameTime();

protected:
	GameTime();

};

#endif