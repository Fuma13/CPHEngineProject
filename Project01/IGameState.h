#ifndef __IGameState_h__
#define __IGameState_h__

#include "EventHandler.h"
//#include "GameObject.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "EGameObject.h"
class GameObject;
using std::vector;

class IGameState
{

//private:
	//vector<GameObject*> vector_of_game_object;//list containing all the game objects connected with this frame listener
public:
	#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX IGameState included")

	//IGameState();
	
	virtual void init() = 0;
	
	// virtual void destroy();

	// virtual void pause();
	// virtual void resume();

	// virtual bool update();
	// virtual void handleEvents() ;

	/* For optimization use EGameObject instead of GameObject*/
	//virtual void spawnGameObject(GameObject* game_obj);
	
	/* For optimization use EGameObject instead of GameObject*/
	//virtual void spawnGameObject(GameObject* game_obj, Vector3 position);
	
	/* For optimization use EGameObject instead of GameObject
	@Param rotation: You can pass Quaternion.identity*/
	//virtual void spawnGameObject(GameObject* game_obj, Vector3 position, Quaternion orientation);
	
	/*Passing an enum is more efficient, but requires the user of the engine to list it as EGameObject*/
	//virtual void spawnGameObject(EGameObject type);
	
	/*Passing an enum is more efficient, but requires the user of the engine to lsit it as EGameObject*/
	//virtual void spawnGameObject(EGameObject type, Vector3 position);
	
	/*Passing an enum is more efficient, but requires the user of the engine to list it as EGameObject
	@Param rotation: You can pass Quaternion.identity*/
	// virtual void spawnGameObject(EGameObject type, Vector3 position, Quaternion orientation);

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