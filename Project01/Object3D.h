#ifndef __Object3D_H
#define __Object3D_H

//#include "GameObject.h"
class TransformNode;
//#include "SceneManager.h"
class Vector3;
#include "Quaternion.h"


class Object3D 
{
protected:
	//TransformNode* m_transformNode;
	
public:
#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX Object3D included")
	Object3D();
	Object3D(Vector3 position, Quaternion orientation); //: public GameObject();
	//virtual void update(vector<Event*> events);
	//virtual void setter();
};

#endif

