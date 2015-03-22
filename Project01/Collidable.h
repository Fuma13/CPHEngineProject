#ifndef __Collidable_h__
#define __Collidable_h__


#include "Matrix4.h"
#include "MemoryManager.h"
#include <iostream>

class GameObject;
class Collidable
{
	public:
		void raise(int n_value);
		Collidable(GameObject* object_attached);
		void drawBoundingBox();
		void printBoundingBoxPoint();
		~Collidable();
		void setTransformationAtOBB();
		Vector3 getBoundingBox(int index);
		static const int bounding_box_dimension;
		GameObject* getGameObject();

	private:
		__event void MyEvent(int n_value);

		void setOrientedBoundingBox();
		void stampMatrix();

		Vector3* m_bounding_box;
		Vector3* m_bounding_box_trans;
		GameObject* m_object_attached;
		Matrix4 tranform_matrix;
		


};


#endif