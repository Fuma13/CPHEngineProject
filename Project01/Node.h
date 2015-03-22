#ifndef __Node_H__
#define __Node_H__

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include <list>
#include <string>
#include "Mesh.h"

class Node{
	
	public:
	
		#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX Node included")

		//Method to create a child of a Node.
		virtual Node * createChild(const std::string & stringName);
		
		//Method to get the name of this Node
		virtual std::string getName();
		
		//A Node can have an object attached.
		virtual void attachObject();
		
		//This method provides a pointer of a list of pointers of all object attached to the node
		virtual std::list<Mesh*> * getAttachedObjectPtr();
		
		/*This method returns a pointer to the parent of the TransformNode. Noticed that the parent of the
		Root is the same Root*/
		virtual Node * getParent();
		
		//This metod allows to change the parent in runtime attaching the TranformNode to another parent
		virtual void changeParent(Node * new_parent);
		
		//This method returns a pointer of a list of pointers of all the children of the Node
		virtual void getChildrenPtr();
		
		virtual ~Node(){delete this;}

	protected:

		/*Constructor. Nodes’s constructor needs a string that 
		identify the node’s name.s
		Notice that if you want to create a Node you need to call 
		the method createChild, since all Nodes are children of a 
		Root. If you want to create a node that is child of the 
		Root you have to call the method getRootNode.*/
		Node(const std::string & stringName);
		virtual void matchNames ( std::string matching_name);
		virtual void setParent(Node * parent);
		virtual void deleteChild (Node * child_ptr);
		virtual void insertChildInList(Node * new_child);

};

#endif