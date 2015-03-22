#ifndef __TransformNode_H__
#define __TransformNode_H__

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include <list>
#include <string>
#include "Mesh.h"
#include "Math.h"
#include "Vector3.h"
#include "Node.h"
#include "MovableObject.h"
#include "Matrix3.h"
#include <sstream>
class Collidable;

class TransformNode : public MovableObject
{
	friend class PhysicsManager;

	public:

		int testing_coder;

		#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX TransformNode included")

		//Method to create a child of a TransformNode.
		TransformNode * createChild(const std::string & stringName, Vector3 initial_position = Vector3::ZERO);
		
		//Method to delete child of a transform node
		void deleteChild (TransformNode * child_ptr);

		//Method to get the name of this TransformNode
		std::string getName();
		
		//A TranformNode can have an object attached like a mesh.
		void attachObject(Mesh * mesh_ptr);
		
		//This method updates all its transformations and the transformations of all the children
		void updateNode ();
		
		//This method provides a pointer of a list of pointers of all object attached to the node
		std::list<Mesh*> * getAttachedObjectPtr();

		std::list<Collidable*> * getAttachedCollidablePtr();
		
		/*This method returns a pointer to the parent of the TransformNode. Noticed that the parent of the
		Root is the same Root*/
		TransformNode * getParent();
		
		//This metod allows to change the parent in runtime attaching the TranformNode to another parent
		void changeParent(TransformNode * new_parent,Vector3 initial_position = Vector3::ZERO);
		
		//This method returns a pointer of a list of pointers of all the children of the TranformNode
		std::list<TransformNode*> * getChildrenPtr();

		void stampMatrix();


		const Quaternion & getOrientation()  ;
		const Vector3 & getScale() ;
		const Vector3 & getPosition() ;
		//Get the matrix of all transformation for physics
		const Matrix4 & getMatrixTransform();
		void translate (const Vector3& translation_value, TransformSpace relativeTo);
		void setPosition(const Vector3& position_value);
		void rotate(const Vector3& axis, const Radian& angle, TransformSpace relativeTo);
		void rotate(const Quaternion& rotation_value, TransformSpace relativeTo);
		void roll(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);
        void pitch(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);
        void yaw(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);
		void setOrientation(const Quaternion & orientation_value);
		void scale(const Vector3& scale_value);
		void setScale(const Vector3& scale_value);
		
		~TransformNode(){delete this;}

		//moved this here, tilman 15.12.2011
		Matrix3 getLocalAxes();


	protected:

		/*Constructor. TransformNodes’s constructor needs a string that 
		identify the node’s name and a Vector3 and Quaternion to specify 
		the position and the orientation of the node according to his parent. 
		Notice that if you want to create a TransformNode you need to call 
		the method createChild, since all TranformNodes are children of a 
		Root that is automatically created by the SceneManager. If you want 
		to create a node that is child of the Root you have to call the method 
		getRootTranformNode from the SceneManager.*/
		TransformNode(const std::string & stringName,Vector3 initial_position = Vector3::ZERO);

		std::list<TransformNode*> child_list;
		std::string node_name;
		//Mesh * mesh_attached;
		std::list<Mesh*> attached_obj;
		//Only for physics
		std::list<Collidable*> attached_collidable;
		//float translate_ratio;
		void matchNames ( std::string matching_name);
		void setParent(TransformNode * parent);
		TransformNode * parent_ptr;
		
		void insertChildInList(TransformNode * new_child);
		Matrix4 global_transform;
		GLfloat arr[16];
		GLfloat arr2[16];
		Matrix4 getParentTransform() ;
		void convertMatrixToFloat();
		void convertFloatToMatrix();
		

	//private:
	
		void attachCollidable(Collidable * coll_ptr);

		//Material * mat02;
};

#endif