#include "Root.h"

Root * Root::p_instance = NULL;

Root::Root()
{
	// !
	// NEVER CALL ANY INSTANCE OF A SINGLETON HERE! Use init instead!!!
	// !
}

Root * Root::getInstance()
{
	if(p_instance == NULL)
	{
		p_instance = new (EAllocationType::ROOT) Root();
	}
	return p_instance;
}

void Root::init() //;
{
	//And first, there was time (what else?)
	mGameTime = GameTime::getInstance();
	mRenderManager = RenderManager::getInstance();
	mRenderManager->initializeRender();

	mInputManager = InputManager::getInstance();
	mRootTransformNode = RootTransformNode::getInstance("Root");
	msc = SceneManager::getInstance();
	//get Instance to make sure a GameStateManager has been constructed

	mAIManager = AI_Manager::getInstance();
	mAIGameModel = AI_GameModel::getInstance();
	mPhysicsManager = PhysicsManager::getInstance();
	mPhysicsManager->init();

	mGameStateManager = GameStateManager::getInstance();
	mGameStateManager->init();
	
	mGameLoop = GameLoop::getInstance();

	//msc->initializeEngine();
	mGameLoop->startEngine(true,60,10);
}

//this was to illustrate a design in which all communication between managers would happen
//through the root
void Root::handleInput()
{
	//let the InputManager do its job
	mInputManager->handle_input();
}

void Root::updateGameState(vector<Event*> events)
{
	mGameStateManager->update(events);
}