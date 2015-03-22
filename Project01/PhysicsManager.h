#ifndef PhysicsManager_H
#define PhysicsManager_H

#include "MemoryManager.h"
#include "TransformNode.h"
#include "SceneManager.h"
#include "Collidable.h"
#include "GJK.h"
#include "RigidBody.h"
#include "Prova.h"



#pragma once

class PhysicsManager
{

	public:
		static PhysicsManager * getInstance ();
		Collidable* attachCollidable(GameObject* game_obj);
		TransformNode* getPhysicTransformNode();
		void collisionDetector();
		void removeCollidable(Collidable * coll_ptr);

		void init();

	private:
		PhysicsManager();
		static PhysicsManager * m_instance;
		
		GJK* m_gjk;
		TransformNode* m_transform_node;
		int count;
		bool collision;
};

#endif