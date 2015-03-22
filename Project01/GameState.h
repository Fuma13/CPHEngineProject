#ifndef __IGameState_h__
#define __IGameState_h__

#include "EventHandler.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "EGameObject.h"
#include <string>
#include <vector>
#include "MemoryManager.h"
class GameObject;
using namespace std;

//This is the not(?) purely abstract base class for game states
class GameState
{
protected:
	string name;
	vector<GameObject*> vector_of_game_object;//list containing all the game objects connected with this frame listener
public:
	GameState(){name = "abstract base class for GameState";};

	virtual void init() = 0;
	virtual string get_name() =0;//;
	//{ return name;}
	
	virtual void destroy() = 0;

	// virtual void pause();
	// virtual void resume();

	virtual bool update(vector<Event*> events) = 0;
	// virtual void handleEvents() ;

	/* For optimization use EGameObject instead of GameObject*/
	//virtual void spawnGameObject(GameObject* game_obj);
	
	/* For optimization use EGameObject instead of GameObject*/
	//virtual void spawnGameObject(GameObject* game_obj, Vector3 position);
	
	/* For optimization use EGameObject instead of GameObject
	@Param rotation: You can pass Quaternion.identity*/
	virtual void spawnGameObject(GameObject* game_obj, Vector3 position, Quaternion orientation) = 0;
	
	/*Passing an enum is more efficient, but requires the user of the engine to list it as EGameObject*/
	//virtual void spawnGameObject(EGameObject type);
	
	/*Passing an enum is more efficient, but requires the user of the engine to lsit it as EGameObject*/
	//virtual void spawnGameObject(EGameObject type, Vector3 position);
	
	/*Passing an enum is more efficient, but requires the user of the engine to list it as EGameObject
	@Param rotation: You can pass Quaternion.identity*/
	virtual void spawnGameObject(EGameObject type, Vector3 position, Quaternion orientation) = 0;

	/* For optimization use EGameObject instead of GameObject*/
	// virtual void destroyGameObject(GameObject* game_obj);
	
	/* For optimization use EGameObject instead of GameObject*/
	// virtual void destroyGameObject(GameObject* game_obj, Vector3 position);
	
	/* For optimization use EGameObject instead of GameObject
	@Param rotation: You can pass Quaternion.identity*/
	// virtual void destroyGameObject(GameObject* game_obj, Vector3 position, Quaternion orientation);
	
	/*Passing an enum is more efficient, but requires the user of the engine to list it as EGameObject*/
	// virtual void destroyGameObject(EGameObject type);
	
	/*Passing an enum is more efficient, but requires the user of the engine to lsit it as EGameObject*/
	// virtual void destroyGameObject(EGameObject type, Vector3 position);
	
	/*Passing an enum is more efficient, but requires the user of the engine to list it as EGameObject
	@Param rotation: You can pass Quaternion.identity*/
	// virtual void destroyGameObject(EGameObject type, Vector3 position, Quaternion orientation);
};

#endif