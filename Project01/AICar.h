#ifndef AICar_H
#define AICar_H

#include "GameObject.h"
#include "Quaternion.h"
#include "Vector3.h"
#include <string>
class GameObject;

using namespace::std;

class AICar : public GameObject
{
//private:
public:
	AICar();
	AICar(string name, Vector3 position = Vector3::ZERO, Quaternion orientation = Quaternion::IDENTITY) : GameObject(name, position, orientation){};
	~AICar();

	void init(int code);
	void destroy();
	void update(vector<Event*> events){};
	void onAI();
};

#endif
