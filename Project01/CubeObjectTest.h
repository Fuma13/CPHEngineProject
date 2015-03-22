#ifndef CubeObjectTest_H
#define CubeObjectTest_H

#include "GameObject.h"
#include "Quaternion.h"
#include "Vector3.h"
#include <string>

using namespace::std;

class CubeObjectTest : public GameObject//, IObject3D/*: public Object3D, public GameObject*/
{
//private:
public:
	CubeObjectTest();
	CubeObjectTest(string name, Vector3 position = Vector3::ZERO, Quaternion orientation = Quaternion::IDENTITY) : GameObject(name, position, orientation){};
	~CubeObjectTest();

	void init(int code);
	void destroy();

	void update(vector<Event*> events){};
};

#endif
