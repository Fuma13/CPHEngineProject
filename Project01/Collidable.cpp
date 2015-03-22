#include "Collidable.h"
#include"GameObject.h"

const int Collidable::bounding_box_dimension = 8;

Collidable::Collidable(GameObject* object_attached)
{
	m_object_attached = object_attached;
	m_bounding_box = new (EAllocationType::PHYSICS) Vector3[8];
	m_bounding_box_trans = new (EAllocationType::PHYSICS) Vector3[8];
	setOrientedBoundingBox();
}

Collidable::~Collidable()
{
	PhysicsManager::getInstance()->removeCollidable(this);
	m_bounding_box = nullptr;
	m_bounding_box_trans = nullptr;
	m_object_attached = nullptr;
	//delete m_bounding_box;
}

void Collidable::raise (int n_value)
{ 
	__raise MyEvent(n_value);
}

void Collidable::setOrientedBoundingBox()
{
	Vector3 min = Vector3(99999.0f,99999.0f,99999.0f);
	Vector3 max = Vector3(-99999.0f,-99999.0f,-99999.0f);
	Vector3* temp_vertices;
	int count_vertices = 0;

	if( m_object_attached->mMesh->hasSubMesh())
	{
		std::map<std::string, Mesh*>::iterator iter;
		for(iter = m_object_attached->mMesh->sub_mesh_tab.begin();  iter != m_object_attached->mMesh->sub_mesh_tab.end(); ++iter)
		{
			count_vertices += iter->second->getNumVertices();
		}
		temp_vertices = new Vector3[count_vertices];

		int k=0;
		for(iter = m_object_attached->mMesh->sub_mesh_tab.begin();  iter != m_object_attached->mMesh->sub_mesh_tab.end(); ++iter)
		{
			Vector3* temp_sub_mesh_vertices = iter->second->getVertices();
			for(int i=0; i < iter->second->getNumVertices(); i++)
			{
				temp_vertices[k] = temp_sub_mesh_vertices[i];
				k++;
			}
		}

	}
	else
	{
		temp_vertices = m_object_attached->mMesh->getVertices();
	}

	Vector3 item;
	for (int i = 0; i< count_vertices; i++)
	{
		item = temp_vertices[i];
		if(item.x < min.x)
			min.x = item.x;
		if(item.y < min.y)
			min.y = item.y;
		if(item.z < min.z)
			min.z = item.z;

		if(item.x > max.x)
			max.x = item.x;
		if(item.y > max.y)
			max.y = item.y;
		if(item.z > max.z)
			max.z = item.z;
	}


	m_bounding_box[0].x = min.x;
	m_bounding_box[0].y = min.y;
	m_bounding_box[0].z = min.z;

	m_bounding_box[1].x = max.x;
	m_bounding_box[1].y = min.y;
	m_bounding_box[1].z = min.z;

	m_bounding_box[2].x = max.x;
	m_bounding_box[2].y = min.y;
	m_bounding_box[2].z = max.z;

	m_bounding_box[3].x = min.x;
	m_bounding_box[3].y = min.y;
	m_bounding_box[3].z = max.z;

	m_bounding_box[4].x = min.x;
	m_bounding_box[4].y = max.y;
	m_bounding_box[4].z = min.z;

	m_bounding_box[5].x = max.x;
	m_bounding_box[5].y = max.y;
	m_bounding_box[5].z = min.z;

	m_bounding_box[6].x = max.x;
	m_bounding_box[6].y = max.y;
	m_bounding_box[6].z = max.z;

	m_bounding_box[7].x = min.x;	
	m_bounding_box[7].y = max.y;
	m_bounding_box[7].z = max.z;

}

void Collidable::drawBoundingBox()
{
	//stampMatrix();

	//cout<<"paufydhjic"<<endl;

	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0);

	glVertex3f(m_bounding_box_trans[0].x,m_bounding_box_trans[0].y,m_bounding_box_trans[0].z);
	glVertex3f(m_bounding_box_trans[1].x,m_bounding_box_trans[1].y,m_bounding_box_trans[1].z);

	glVertex3f(m_bounding_box_trans[1].x,m_bounding_box_trans[1].y,m_bounding_box_trans[1].z);
	glVertex3f(m_bounding_box_trans[2].x,m_bounding_box_trans[2].y,m_bounding_box_trans[2].z);

	glVertex3f(m_bounding_box_trans[2].x,m_bounding_box_trans[2].y,m_bounding_box_trans[2].z);
	glVertex3f(m_bounding_box_trans[3].x,m_bounding_box_trans[3].y,m_bounding_box_trans[3].z);

	glVertex3f(m_bounding_box_trans[3].x,m_bounding_box_trans[3].y,m_bounding_box_trans[3].z);
	glVertex3f(m_bounding_box_trans[0].x,m_bounding_box_trans[0].y,m_bounding_box_trans[0].z);

	glVertex3f(m_bounding_box_trans[4].x,m_bounding_box_trans[4].y,m_bounding_box_trans[4].z);
	glVertex3f(m_bounding_box_trans[5].x,m_bounding_box_trans[5].y,m_bounding_box_trans[5].z);

	glVertex3f(m_bounding_box_trans[5].x,m_bounding_box_trans[5].y,m_bounding_box_trans[5].z);
	glVertex3f(m_bounding_box_trans[6].x,m_bounding_box_trans[6].y,m_bounding_box_trans[6].z);

	glVertex3f(m_bounding_box_trans[6].x,m_bounding_box_trans[6].y,m_bounding_box_trans[6].z);
	glVertex3f(m_bounding_box_trans[7].x,m_bounding_box_trans[7].y,m_bounding_box_trans[7].z);

	glVertex3f(m_bounding_box_trans[7].x,m_bounding_box_trans[7].y,m_bounding_box_trans[7].z);
	glVertex3f(m_bounding_box_trans[4].x,m_bounding_box_trans[4].y,m_bounding_box_trans[4].z);

	glVertex3f(m_bounding_box_trans[0].x,m_bounding_box_trans[0].y,m_bounding_box_trans[0].z);
	glVertex3f(m_bounding_box_trans[4].x,m_bounding_box_trans[4].y,m_bounding_box_trans[4].z);

	glVertex3f(m_bounding_box_trans[1].x,m_bounding_box_trans[1].y,m_bounding_box_trans[1].z);
	glVertex3f(m_bounding_box_trans[5].x,m_bounding_box_trans[5].y,m_bounding_box_trans[5].z);

	glVertex3f(m_bounding_box_trans[2].x,m_bounding_box_trans[2].y,m_bounding_box_trans[2].z);
	glVertex3f(m_bounding_box_trans[6].x,m_bounding_box_trans[6].y,m_bounding_box_trans[6].z);

	glVertex3f(m_bounding_box_trans[3].x,m_bounding_box_trans[3].y,m_bounding_box_trans[3].z);
	glVertex3f(m_bounding_box_trans[7].x,m_bounding_box_trans[7].y,m_bounding_box_trans[7].z);

	glEnd();
}

void Collidable::printBoundingBoxPoint()
{

	std::cout<< m_bounding_box_trans[0].x << "     "<<m_bounding_box_trans[0].y <<"     "<< m_bounding_box_trans[0].z << endl;
	std::cout<< m_bounding_box_trans[1].x << "     "<<m_bounding_box_trans[1].y <<"     "<< m_bounding_box_trans[1].z << endl;
	std::cout<< m_bounding_box_trans[2].x << "     "<<m_bounding_box_trans[2].y <<"     "<< m_bounding_box_trans[2].z << endl;
	std::cout<< m_bounding_box_trans[3].x << "     "<<m_bounding_box_trans[3].y <<"     "<< m_bounding_box_trans[3].z << endl;
	std::cout<< m_bounding_box_trans[4].x << "     "<<m_bounding_box_trans[4].y <<"     "<< m_bounding_box_trans[4].z << endl;
	std::cout<< m_bounding_box_trans[5].x << "     "<<m_bounding_box_trans[5].y <<"     "<< m_bounding_box_trans[5].z << endl;
	std::cout<< m_bounding_box_trans[6].x << "     "<<m_bounding_box_trans[6].y <<"     "<< m_bounding_box_trans[6].z << endl;
	std::cout<< m_bounding_box_trans[7].x << "     "<<m_bounding_box_trans[7].y <<"     "<< m_bounding_box_trans[7].z << endl;
}

void Collidable::setTransformationAtOBB()
{
	tranform_matrix = m_object_attached->mTransformNode->getMatrixTransform();

	for(int i=0; i < bounding_box_dimension; i++)
	{
		//take original position
		m_bounding_box_trans[i] = m_bounding_box[i];
		//aplly scale
		//m_bounding_box_trans[i] = m_bounding_box_trans[i] * tranform_matrix.getScale();
		//apply rotation
		Vector4 pos_temp = Vector4(m_bounding_box_trans[i].x,m_bounding_box_trans[i].y,m_bounding_box_trans[i].z,1);
		pos_temp = tranform_matrix * pos_temp;
		//std::cout<< "vector4:"<< i <<"    "<< pos_temp.x << "     "<<pos_temp.y <<"     "<< pos_temp.z << pos_temp.w<<"    " << endl;
		m_bounding_box_trans[i] = pos_temp.xyz();

		//apply translation
		//m_bounding_box_trans[i] = m_bounding_box_trans[i] + tranform_matrix.getTrans();
	}
}

void Collidable::stampMatrix(){

	for (int i=0;i<4;i++){

		std::cout << tranform_matrix[i][0];
		std::cout << ",";
		std::cout << tranform_matrix[i][1];
		std::cout << ",";
		std::cout << tranform_matrix[i][2];
		std::cout << ",";
		std::cout << tranform_matrix[i][3];
		std::cout << "  " << std::endl;
		
	}
	std::cout<<"     " <<std::endl;

}

Vector3 Collidable::getBoundingBox(int index)
{
	return m_bounding_box_trans[index];
}

GameObject* Collidable::getGameObject()
{
	return m_object_attached;
}
