#include "Collidable.h"
#include <list>
#include "Vector3.h"
#include <vector>

class Prova
{
private:
	static const int max_iterations = 20;
	int count;
	Vector3 m_direction;
	std::list<Vector3> simplex;

	bool updateSimplexAndDirection(std::list<Vector3> simplex, Vector3 direction);
	Vector3 maxPointInMinkDiffAlongDir(Collidable * shape1, Collidable * shape2, Vector3 direction);
	Vector3 maxPointAlongDirection(Collidable * shape, Vector3 direction);

	Vector3 getListAt( int index);
	int sign(float number);



public:
	bool bodiesIntersect(Collidable * shape1, Collidable * shape2);
	Prova();
};