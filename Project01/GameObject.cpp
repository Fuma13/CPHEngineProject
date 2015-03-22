#include "GameObject.h"
#include "Root.h"

GameObject::GameObject(){};

	// Specify exactly one transfrom node if you want to include this into the SceneGraph
GameObject::GameObject(string name, Vector3 position, Quaternion orientation)//;
	{
		Root * mRoot = Root::getInstance(); 
		name_this = name;
		mTransformNode = mRoot->mRootTransformNode->createChild(name);
		collided = false;
	}

void GameObject::init()	
{
	string bla = bla;
}

void GameObject::update(vector<Event*> events){};