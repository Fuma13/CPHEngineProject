#include "GJK.h"

GJK* GJK::m_instance = nullptr;

GJK* GJK::getInstance()
{
	if(m_instance == nullptr)
	{
	
		m_instance = new (EAllocationType::PHYSICS) GJK();

	}

	return m_instance;
}

GJK::GJK()
{
	//simplex = new Vector3[4];
}

GJK::~GJK()
{
	simplex.clear();
}

//Return element in position index from simplex List
Vector3 GJK::getListAt( int index)
{
	std::list<Vector3>::iterator iter = simplex.begin();
	if(index < simplex.size())
	{
		for(int i=0; i<index; i++)
		{
			iter++;
		}
		return *iter;
	}
}

//Return if a number is positive or negative
int GJK::sign(float number)
{
	if(number > 0)
	{
		return 1;
	}
	else if( number = 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/// Given the vertices (in any order) of two convex 3D bodies, calculates whether they intersect 

bool GJK::bodiesIntersect(Collidable * shape1, Collidable * shape2)
{
	Vector3 initialPoint = shape1->getBoundingBox(0) - shape2->getBoundingBox(0);
	Vector3 s = maxPointInMinkDiffAlongDir(shape1,shape2,initialPoint);
	Vector3 d = s.negative();

	simplex.push_back(s);
	count = 0;
	while(count < max_iterations)
	{
		Vector3 a = maxPointInMinkDiffAlongDir(shape1,shape2,d);
		if(a.dotProduct(d) < 0)
		{
			return false;
		}

		simplex.push_back(a);

		if(updateSimplexAndDirection(simplex, d))
		{
			return true;
		}
		count ++;
	}

	return false;
}

/// Updates the current simplex and the direction in which to look for the origin. Called DoSimplex in the video lecture. 
bool GJK::updateSimplexAndDirection(std::list<Vector3> simplex, Vector3 direction)
{
	//if the simplex is a line 
	if(simplex.size() == 2)
	{
		//A is the point added last to the simplex 
		Vector3 a = getListAt(1);
		Vector3 b = getListAt(0);
		Vector3 ab = b - a;
		Vector3 ao = a.negative();

		if(ab.dotProduct(ao) > 0)
		{
			direction = (ab.crossProduct(ao)).crossProduct(ab);
		}
		else
		{
			direction = ao;
		}
	}
	//if the simplex is a triangle
	else if(simplex.size() == 3)
	{
		//A is the point added last to the simplex 
		Vector3 a = getListAt(2);
		Vector3 b = getListAt(1);
		Vector3 c = getListAt(0);

		Vector3 ao = a.negative();
		Vector3 ab = b - a;
		Vector3 ac = c - a;
		Vector3 abc = ab.crossProduct(ac);

		if((abc.crossProduct(ac)).dotProduct(ao) > 0)
		{
			if(ac.dotProduct(ao) > 0)
			{
				simplex.clear();
				simplex.push_back(c);
				simplex.push_back(a);
				direction = (ac.crossProduct(ao)).crossProduct(ac);
			}
			else if(ab.dotProduct(ao) > 0)
			{
				simplex.clear();
				simplex.push_back(b);
				simplex.push_back(a);
				direction = (ac.crossProduct(ao)).crossProduct(ab);
			}
			else
			{
				simplex.clear();
				simplex.push_back(a);
				direction = ao;
			}
		}
		else
		{
			if((ab.crossProduct(abc)).dotProduct(ao) > 0)
			{
				if(ab.dotProduct(ao) > 0)
				{
					simplex.clear();
					simplex.push_back(b);
					simplex.push_back(a);
					direction = (ab.crossProduct(ao)).crossProduct(ab);
				}
				else
				{
					simplex.clear();
					simplex.push_back(a);
					direction = ao;
				}
			}
			else
			{
				if(abc.dotProduct(ao) > 0)
				{
					 //the simplex stays A, B, C
					direction = abc;
				}
				else
				{
					simplex.clear();
					simplex.push_back(b);
					simplex.push_back(c);
					simplex.push_back(a);
					direction = abc.negative();
				}
			}
		}
	}
	//if the simplex is a tetrahedron
	else //if (simplex.size() == 4)
	{
		//A is the point added last to the simplex 
		Vector3 a = getListAt(3);
		Vector3 b = getListAt(2);
		Vector3 c = getListAt(1);
		Vector3 d = getListAt(0);

		Vector3 ao = a.negative();
		Vector3 ab = b - a;
		Vector3 ac = c - a;
		Vector3 ad = d - a;
		Vector3 abc = ab.crossProduct(ac);
		Vector3 acd = ac.crossProduct(ad);
		Vector3 adb = ad.crossProduct(ab);

		//the side (positive or negative) of B, C and D relative to the planes of ACD, ADB and ABC respectively
		int b_side_on_acd = sign(acd.dotProduct(ab));
		int c_side_on_adb = sign(adb.dotProduct(ac));
		int d_side_on_abc = sign(abc.dotProduct(ad));

		//whether the origin is on the same side of ACD/ADB/ABC as B, C and D respectively 
		bool ab_same_as_origin = (sign(acd.dotProduct(ao)) == b_side_on_acd);
		bool ac_same_as_origin = (sign(adb.dotProduct(ao)) == c_side_on_adb);
		bool ad_same_as_origin = (sign(abc.dotProduct(ao)) == d_side_on_abc);

		//if the origin is on the same side as all B, C and D, the origin is inside the tetrahedron and thus there is a collision 
		if(ab_same_as_origin && ac_same_as_origin && ad_same_as_origin)
		{
			return true;
		}
			//if the origin is not on the side of B relative to ACD 
		else if(!ab_same_as_origin)
		{
			//B is farthest from the origin among all of the tetrahedron's points, so remove it from the list and go on with the triangle case 
			simplex.remove(b);
			//the new direction is on the other side of ACD, relative to B 
			direction = acd * -b_side_on_acd;
		}
			//if the origin is not on the side of C relative to ADB 
		else if(!ac_same_as_origin)
		{
			//C is farthest from the origin among all of the tetrahedron's points, so remove it from the list and go on with the triangle case 
			simplex.remove(c); 
			//the new direction is on the other side of ADB, relative to C 
			direction = adb * -c_side_on_adb; 
		}
			//if the origin is not on the side of D relative to ABC 
		else //if(!ad_same_as_origin)
		{
            //D is farthest from the origin among all of the tetrahedron's points, so remove it from the list and go on with the triangle case 
            simplex.remove(d); 
            //the new direction is on the other side of ABC, relative to D 
            direction = abc * -d_side_on_abc;
		}
		//go on with the triangle case
		return updateSimplexAndDirection(simplex, direction);
	}
	//no intersection found on this iteration 
    return false;
}


/// Finds the farthest point along a given direction of the Minkowski difference of two convex polyhedra. 
/// Called Support in the video lecture: max(D.Ai) - max(-D.Bj) 
Vector3 GJK::maxPointInMinkDiffAlongDir(Collidable* shape1, Collidable* shape2, Vector3 direction)
{
	return (maxPointAlongDirection(shape1,direction) - maxPointAlongDirection(shape2, direction.negative()));
}

/// Finds the farthest point along a given direction of a convex polyhedron 
Vector3 GJK::maxPointAlongDirection(Collidable * shape, Vector3 direction)
{
	float max = -9999999999999999999.0f;
    int index = 0;
    for (int i = 0; i < Collidable::bounding_box_dimension; i++)
    {
		float dot = shape->getBoundingBox(i).dotProduct(direction);
        if (dot > max)
        {
            max = dot;
            index = i;
        }
    }
    return shape->getBoundingBox(index);
}

