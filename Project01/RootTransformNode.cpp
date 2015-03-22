#include "RootTransformNode.h"


RootTransformNode::RootTransformNode(const std::string & stringName,Vector3 initial_position ) : TransformNode(stringName,initial_position){

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
}

RootTransformNode * RootTransformNode::p_instance = NULL;

RootTransformNode * RootTransformNode::getInstance(const std::string & stringName,Vector3 initial_position ){

	if(p_instance == NULL){
	
		p_instance = new RootTransformNode(stringName,initial_position);

	}

	return p_instance;

}

