#ifndef __GameObject_H__
#define __GameObject_H__

#include "event.h"
#include <vector>
#include <string>
#include "Vector3.h"
#include "Quaternion.h"
#include "ResourceManager.h"
#include "Mesh.h"

//#include "TransformNode.h"
#include "Material.h"

#include "PhysicsManager.h"

//class Collidable;
class AI_Agent;

using namespace std;

class GameObject
{
private:
protected:
	//Collidable * mCollidable
public:
#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX GameObject included")
	
	TransformNode * mTransformNode;
	Mesh * mMesh;
	RigidBody * mRigidBody;
	Collidable* mCollidable;
	AI_Agent* mAgent;
	bool collided;
	GameObject* collide_with;
	
	string name_this;

	GameObject();

	// Specify exactly one transfrom node if you want to include this into the SceneGraph
	GameObject(string name, Vector3 position = Vector3::ZERO, Quaternion orientation = Quaternion::IDENTITY);

/*
	GameObject(){};
	GameObject(string name)
	{
		name_this = name;
		// If Game Object should be part of SceneGraph do something like this:
		// TransformNode tn = SceneManager::getInstance()->getRootTransformNode()->createChild("node6");
	}
*/
	/*virtual*/ 
	void init();
	//virtual void destroy() = 0;
	virtual void update(vector<Event*> events);

};

#endif

