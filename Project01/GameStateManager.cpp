#include "GameStateManager.h"
#include "GamePlay_01.h"
#include "GamePlay_02.h"
#include "GamePlay_03.h"

GameStateManager * GameStateManager::p_instance = NULL;

GameStateManager::GameStateManager()
{
}

GameStateManager * GameStateManager::getInstance()
{
	if(p_instance == NULL)
	{
		p_instance = new (EAllocationType::GAMEOBJECTS) GameStateManager();
	}
	return p_instance;
}

GameState* GameStateManager::get_currentGameState()
{
	return currentGameState;
}

bool GameStateManager::init()
{
	gamePlay_01 = GamePlay_01::getInstance();
	gamePlay_01->init();
	gameStates.push_back(gamePlay_01);

	gamePlay_02 = GamePlay_02::getInstance();
	//gamePlay_02->init();
	gameStates.push_back(gamePlay_02);

	gamePlay_03 = GamePlay_03::getInstance();
	//gamePlay_02->init();
	gameStates.push_back(gamePlay_03);

	currentGameState = gameStates[0];

	return true;
}

bool GameStateManager::update(vector<Event*> events)
{
	//cout << "in gamestatemanager update" << endl;
	//gameStates.back()...
	currentGameState->update(events);
	
	return 0;
}

bool GameStateManager::transitToGameState(EGameState state)
{
	//cout << "GS " << state <<endl;
	currentGameState->destroy();
	//delete  dynamic_cast<(typeid (currentGameState))> (currentGameState);
	currentGameState = gameStates[state];
	currentGameState->init();
	return true;
}