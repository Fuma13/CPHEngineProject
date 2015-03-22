#include "AICar.h"
#include "GameObject.h"
#include "AI_Manager.h"
#include "AI_GameModel.h"

AICar::AICar(){}

/*
CubeObjectTest::CubeObjectTest(string name, Vector3 position, Quaternion orientation) : GameObject(name, position, orientation)
{

}
*/

AICar::~AICar()
{
	TransformNode * parent = mTransformNode->getParent();
	parent->deleteChild(mTransformNode);
	mCollidable->~Collidable();
	MemoryManagement::operator delete (mCollidable,EAllocationType::NO_ASSIGNED) ;
}

void AICar::init(int code)
{
	mMesh = ResourceManager::getInstance()->loadMesh("Data/car2.obj");
	mTransformNode->attachObject(mMesh);
	mCollidable = PhysicsManager::getInstance()->attachCollidable(this);
	mAgent = AI_Manager::getInstance()->get_AIAgent(name_this);
	collided = false;
	collide_with = nullptr;
}

void AICar::onAI()
{
	if(collide_with != nullptr)
	{
		//We inform the knowledge base of the game about the collision.
		AI_GameModel::getInstance()->set_collision_with(name_this, collide_with->name_this);
	}
	else
	{
		AI_GameModel::getInstance()->set_NOcollision(name_this);
	}

	if(mAgent->move_backwards)
	{
		mTransformNode->setPosition(Vector3(0.0,0.0,0.0));
	}

}