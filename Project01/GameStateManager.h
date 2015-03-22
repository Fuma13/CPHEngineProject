#ifndef __GameStateManager_h__
#define __GameStateManager_h__
#pragma once

#include <vector>
#include <sys/types.h>
#include "ConfigurationEnums.h"
#include "MemoryManager.h"
class Event;
using namespace std;

class GamePlay_01;
class GamePlay_02;
class GamePlay_03;
class GameState;

class GameStateManager
{
public:
	static GameStateManager * getInstance ();

	GameState* get_currentGameState();

	/*use this to initialize all game states that are listes in the ConfigurationEnums*/
	bool init();
	/*pass the vector of events to the game state that currently has focus*/
	bool update(vector<Event*> events);
	/*Change game state. @Param EGameState: state you want to switch to*/
	bool transitToGameState(EGameState state);

protected:
	GameStateManager();

private:
	static GameStateManager * p_instance;
	~GameStateManager();

	vector<GameState*> gameStates;

	GamePlay_01 * gamePlay_01;
	GamePlay_02 * gamePlay_02;
	GamePlay_03 * gamePlay_03;
	
	GameState * currentGameState;
};


#endif