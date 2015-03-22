#ifndef __Root_H__
#define __Root_H__
#pragma once

#include "MemoryManagement.h"
#include "SceneManager.h"
#include "GameStateManager.h"
#include "InputManager.h"
#include "GameLoop.h"
#include "RootTransformNode.h"
#include "RenderManager.h"
#include "AI_Manager.h"
#include "GameTime.h"
#include "PhysicsManager.h"
#include "AI_GameModel.h"

class GameState;
class Event;

/*Systems should only know the top level of all the sub systems*/
class Root
{
public:
	static Root * getInstance();
	
	//singetons
	SceneManager* msc;
	InputManager* mInputManager;
	GameStateManager* mGameStateManager;
	RootTransformNode* mRootTransformNode;
	RenderManager* mRenderManager;
	GameLoop*  mGameLoop;
	AI_Manager * mAIManager;
	AI_GameModel* mAIGameModel;
	//ResourceManager * mResourceManager;
	GameTime * mGameTime;
	PhysicsManager * mPhysicsManager;
	

	/*
		- Initialize all the Singletons
		- start the Engine
	*/
	void init();

	/*Ask InputManager to do its job*/
	void handleInput();

	/*Update the GameState*/
	void updateGameState(vector<Event*> events);

private:
	
	static Root* p_instance;
	~Root();
protected:
	Root();

};

#endif
