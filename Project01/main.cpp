/*
 * This is template created for Game Engines 2011 based on the SDL examples from http://nehe.gamedev.net/
 */
#include <iostream>
#include "SceneManager.h"
#include "Root.h"

class GameState;

/* Define our booleans */
#define TRUE  1
#define FALSE 0

int main( int argc, char **argv )
{

	try
	{
		

		Root * mRoot = Root::getInstance();
		mRoot->init();


		//cout << "listen: " << mRoot->currentGameState()->get_name() << endl;

		//GameStateManager * gsm = GameStateManager::getInstance();

		//SceneManager * msc = SceneManager::getInstance();
		//SceneManager * msce = SceneManager::getInstance();
		//msc->initializeEngine();
		//msc->startEngine(true,60,10);


		/* Should never get here */
		return( 0 );
	}
		catch(char e)
		{		
			std::cout << "error  " << e << std::endl; 
		}
}
