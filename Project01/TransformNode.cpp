#include "TransformNode.h"
#include "SceneManager.h"
#include "GamePlay_01.h"
#include "Collidable.h"

TransformNode::TransformNode(const std::string & stringName, Vector3 initial_position ){

	node_name = stringName;
	global_transform = Matrix4::IDENTITY;

	arr[0] = 1 ;
	arr[1] =0 ;
	arr[2] = 0;
	arr[3] = 0;
	arr[4] = 0;
	arr[5] = 1;
	arr[6] = 0;
	arr[7] = 0;
	arr[8] =0 ;
	arr[9] = 0;
	arr[10] = 1;
	arr[11] = 0;
	arr[12] = 0;
	arr[13] = 0;
	arr[14] =0 ;
	arr[15] =1 ;

	//mat02 = new Material("material02");
	//mat02->setDiffiuseColour(0.0,1.0,0.0);

}

TransformNode * TransformNode::createChild(const std::string & stringName, Vector3 initial_position ){

	SceneManager * sc_mn = SceneManager::getInstance();
	sc_mn->getRootTransformNode()->matchNames(stringName);
	TransformNode * temp_node = new TransformNode(stringName, initial_position);
	temp_node->setParent(this);
	child_list.push_back(temp_node);
	
	return temp_node;
	
}

std::string TransformNode::getName(){

	return node_name;
}



void TransformNode::attachObject(Mesh * mesh_ptr)
{

	//mesh_attached = mesh_ptr;
	Mesh * mesh_attached = mesh_ptr;

	if(mesh_attached->hasSubMesh())
	{
		int i=0;
		std::map<std::string, Mesh*>::iterator iter;
		for(iter = mesh_attached->sub_mesh_tab.begin();  iter != mesh_attached->sub_mesh_tab.end(); ++iter)
		{
			std::ostringstream oss;
			oss << i;
			std:: string name = node_name + "_" + oss.str();
			i++;
			TransformNode * child = createChild(name, Vector3(0,0,0));
			child->attachObject(iter->second);
		}
	}
	else
	{
		attached_obj.push_back(mesh_attached);
	}


}

void TransformNode::attachCollidable(Collidable * coll_ptr)
{
	Collidable * collidable_attached = coll_ptr;
	attached_collidable.push_back(collidable_attached);
}

void TransformNode::updateNode()
{

	//translate_ratio = 0.3;
	
	glPushMatrix();
	this->convertMatrixToFloat();
	glMultMatrixf(arr);
	glGetFloatv(GL_MODELVIEW_MATRIX,arr2);
	//global_transform = Matrix4::IDENTITY;
	//this->convertFloatToMatrix();

	//glTranslatef(relative_x,relative_y,relative_z);
	//glRotatef(translate_ratio * 5,0.0,1.0,0.0);
	if(attached_obj.size() != 0) { 
		
		std::list<Mesh*>::iterator it;
		for (it = attached_obj.begin(); it!= attached_obj.end(); ++it)
		{
	
			if((**it).getMaterial() != NULL){
				(**it).getMaterial()->enableMaterial();
				//std::cout << "shader enableddddddddddddd" << std::endl;
				} //mat02->enableMaterial();
			
			(**it).renderMesh();
			//mat02->disableMaterial();
			if((**it).getMaterial() != NULL){
				(**it).getMaterial()->disableMaterial();
			}
			//(**it).drawCube();
		}
	}

	if(attached_collidable.size() != 0)
	{
		std::list<Collidable*>::iterator it;
		for (it = attached_collidable.begin(); it!= attached_collidable.end(); ++it)
		{
			(**it).drawBoundingBox();
			//(**it).getBoundingBoxPoint(1);
		}
	}

	
	if (child_list.size() != 0){

		
		std::list<TransformNode*>::iterator it2;
		for(it2 = child_list.begin(); it2 != child_list.end(); ++it2){
	
			(**it2).updateNode();
	
		}
		
	}
	
	glPopMatrix();

}

std::list<Mesh*> * TransformNode::getAttachedObjectPtr(){

	return &attached_obj;

}

std::list<Collidable*> * TransformNode::getAttachedCollidablePtr()
{
	return &attached_collidable;
}

void TransformNode::setParent(TransformNode * parent){

	parent_ptr = parent;

}

TransformNode * TransformNode::getParent(){

	if (parent_ptr != NULL){
	
		return parent_ptr;
	}

	else {
	
		return this;
	
	}

}

void TransformNode::deleteChild(TransformNode * child_ptr){

	child_list.remove(child_ptr);


}

std::list<TransformNode*> * TransformNode::getChildrenPtr(){

	return &child_list;


}

void TransformNode::changeParent(TransformNode * new_parent,Vector3 initial_position ){

	TransformNode * temp_parent_ptr = this->getParent();
	new_parent->insertChildInList(this);
	temp_parent_ptr->deleteChild(this);
	

}

void TransformNode::insertChildInList(TransformNode * new_child){

	child_list.push_back(new_child);

}

void TransformNode::matchNames(std::string matching_name){

	if (node_name == matching_name){
	
		throw "it works";
	}

	else if (child_list.size() != 0){
	
		std::list<TransformNode*>::iterator it;
		for (it = child_list.begin(); it!= child_list.end(); ++it){
			
			(*it)->matchNames(matching_name);
		
		}
	
	}

}

void TransformNode::stampMatrix(){

	for (int i=0;i<4;i++){

		std::cout << arr2[i];
		std::cout << ",";
		std::cout << arr2[i+4];
		std::cout << ",";
		std::cout << arr2[i+8];
		std::cout << ",";
		std::cout << arr2[i+12];
		std::cout << "  " << std::endl;
		
	}
	std::cout<<"     " <<std::endl;

}


const Quaternion& TransformNode::getOrientation() {

	
	return this->getParentTransform().extractQuaternion();
}

const Vector3 & TransformNode::getScale() {

	return this->getParentTransform().getScale();

}

const Vector3 & TransformNode::getPosition() {

	//global_transform
	
	return this->getParentTransform().getTrans();
}

const Matrix4 & TransformNode::getMatrixTransform()
{
	return this->getParentTransform();
}

void TransformNode::translate (const Vector3& translation_value, TransformSpace relativeTo){
	
	Vector3 temp_position = Vector3::ZERO;
	
	switch(relativeTo)
        {
			
			

        case TS_LOCAL:
            
			// position is relative to parent so transform downwards
			temp_position = global_transform.extractQuaternion() * translation_value;
			global_transform[0][3] += temp_position.x;
			global_transform[1][3] += temp_position.y;
			global_transform[2][3] += temp_position.z;
		        	
			break;
        
		case TS_WORLD:

            // position is relative to parent so transform upwards
			if (this->getParent()->getName() != "root")
            {
				temp_position = (this->getParentTransform().extractQuaternion().Inverse() * translation_value)/this->getParentTransform().getScale();
				global_transform[0][3] += temp_position.x;
				global_transform[1][3] += temp_position.y;
				global_transform[2][3] += temp_position.z;
				
            }
            else
            {
                global_transform[0][3] += temp_position.x;
				global_transform[1][3] += temp_position.y;
				global_transform[2][3] += temp_position.z;
            }
        	
			break;
        
		case TS_PARENT:
				
				global_transform[0][3] += temp_position.x;
				global_transform[1][3] += temp_position.y;
				global_transform[2][3] += temp_position.z;
            
				break;
        }
}

void TransformNode::setPosition(const Vector3& position_value){

	global_transform[0][3] = position_value.x;
	global_transform[1][3] = position_value.y;
	global_transform[2][3] = position_value.z;

}

void TransformNode::rotate(const Vector3& axis, const Radian& angle, TransformSpace relativeTo){

	Quaternion q;
    q.FromAngleAxis(angle,axis);
    rotate(q, relativeTo);
}

void TransformNode::rotate(const Quaternion& rotation_value, TransformSpace relativeTo){

	// Normalise quaternion to avoid drift
		
	Quaternion qnorm = rotation_value;
	qnorm.normalise();
	Matrix3 temp_mt3 = Matrix3::IDENTITY;
	Matrix4 temp_mt4 = Matrix4::IDENTITY;
	Quaternion temp_quat = Quaternion::IDENTITY;
	
       switch(relativeTo)
        {
        case TS_PARENT:
            // Rotations are normally relative to local axes, transform up
			qnorm.ToRotationMatrix(temp_mt3);
			temp_mt4.fromMatrix3(temp_mt3);
			global_transform = temp_mt4 * global_transform;

            break;

        case TS_WORLD:

            // Rotations are normally relative to local axes, transform up
			
			temp_quat = global_transform.extractQuaternion() * this->getParentTransform().extractQuaternion().Inverse() * qnorm * this->getParentTransform().extractQuaternion();
			temp_quat.ToRotationMatrix(temp_mt3);
			temp_mt4.fromMatrix3(temp_mt3);
			global_transform = global_transform * temp_mt4;
			
            break;

        case TS_LOCAL:

            // Note the order of the mult, i.e. q comes after
			qnorm.ToRotationMatrix(temp_mt3);
			temp_mt4.fromMatrix3(temp_mt3);
			global_transform = global_transform * temp_mt4 ;
           
            break;
        }
}

void TransformNode::roll(const Radian& angle, TransformSpace relativeTo ){

	this->rotate(Vector3::UNIT_Z, angle, relativeTo);

}

void TransformNode::pitch(const Radian& angle, TransformSpace relativeTo ){

	this->rotate(Vector3::UNIT_X, angle, relativeTo);
}

void TransformNode::yaw(const Radian& angle, TransformSpace relativeTo ){

	this->rotate(Vector3::UNIT_Y, angle, relativeTo);
}

void TransformNode::setOrientation(const Quaternion & orientation_value){


	Quaternion q = orientation_value;
	q.normalise();
	Matrix3 temp_mt3 = Matrix3::IDENTITY;
	Matrix4 temp_mt4 = Matrix4::IDENTITY;
	Vector3 vt3 = global_transform.getScale();
	temp_mt4[0][0] = temp_mt4[0][0] * vt3.x;
	temp_mt4[1][1] = temp_mt4[1][1] * vt3.y;
	temp_mt4[2][2] = temp_mt4[2][2] * vt3.z;
	q.ToRotationMatrix(temp_mt3);
	temp_mt4.fromMatrix3(temp_mt3);
	//temp_mt4[0][0] = -temp_mt4[0][0];
	//temp_mt4[2][2] = -temp_mt4[2][2];
	//temp_mt4.setScale(global_transform.getScale());
	temp_mt4.setTrans(global_transform.getTrans());
	global_transform = temp_mt4;


}

void TransformNode::scale(const Vector3& scale_value){

	Vector3 sc = global_transform.getScale() + scale_value;
	global_transform.setScale(sc);

}

void TransformNode::setScale(const Vector3& scale_value){

	global_transform.setScale(scale_value);
}

Matrix4 TransformNode::getParentTransform() {

	Matrix4 mt4 = global_transform;
	TransformNode * temp_parent = this->getParent();

	while (temp_parent->getName() != "Root"){
	
		mt4 = temp_parent->global_transform * mt4;
		temp_parent = temp_parent->getParent();
	}

	return mt4;

}

void TransformNode::convertMatrixToFloat(){


	arr[0] = global_transform[0][0];
	arr[4] = global_transform[0][1];
	arr[8] = global_transform[0][2];
	arr[12] = global_transform[0][3];
	arr[1] = global_transform[1][0];
	arr[5] = global_transform[1][1];
	arr[9] = global_transform[1][2];
	arr[13] = global_transform[1][3];
	arr[2] = global_transform[2][0];
	arr[6] = global_transform[2][1];
	arr[10] = global_transform[2][2];
	arr[14] = global_transform[2][3];
	arr[3] = global_transform[3][0];
	arr[7] = global_transform[3][1];
	arr[11] = global_transform[3][2];
	arr[15] = global_transform[3][3];



}

void TransformNode::convertFloatToMatrix(){

	global_transform[0][0] = arr2[0];
	global_transform[0][1] = arr2[4];
	global_transform[0][2] = arr2[8];
	global_transform[0][3] = arr2[12];
	global_transform[1][0] = arr2[1];
	global_transform[1][1] = arr2[5];
	global_transform[1][2] = arr2[9];
	global_transform[1][3] = arr2[13];
	global_transform[2][0] = arr2[2];
	global_transform[2][1] = arr2[6];
	global_transform[2][2] = arr2[10];
	global_transform[2][3] = arr2[14];
	global_transform[3][0] = arr2[3];
	global_transform[3][1] = arr2[7];
	global_transform[3][2] = arr2[11];
	global_transform[3][3] = arr2[15];


}

Matrix3 TransformNode::getLocalAxes(){

	
	Matrix3 return_matrix;
	this->global_transform.extract3x3Matrix(return_matrix);
	return return_matrix;

}