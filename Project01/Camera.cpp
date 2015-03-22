#include "Camera.h"

Camera::Camera (const std::string  & stringName){

	camera_name = stringName;
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

std::string Camera::getName(){


	return camera_name;
}

const Quaternion& Camera::getOrientation() {

	
	return global_transform.extractQuaternion();
}

const Vector3 & Camera::getScale() {

	return global_transform.getScale();

}

const Vector3 & Camera::getPosition() {

	//global_transform
	
	return global_transform.getTrans();
}

void Camera::translate (const Vector3& translation_value, TransformSpace relativeTo){
	
	global_transform[0][3] += translation_value.x;
	global_transform[1][3] += translation_value.y;
	global_transform[2][3] += translation_value.z;
		        	
			
}

void Camera::setPosition(const Vector3& position_value){

	global_transform[0][3] = position_value.x;
	global_transform[1][3] = position_value.y;
	global_transform[2][3] = position_value.z;

}

void Camera::rotate(const Vector3& axis, const Radian& angle, TransformSpace relativeTo){

	Quaternion q;
    q.FromAngleAxis(angle,axis);
    rotate(q, relativeTo);
}

void Camera::rotate(const Quaternion& rotation_value, TransformSpace relativeTo){

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
			
			qnorm.ToRotationMatrix(temp_mt3);
			temp_mt4.fromMatrix3(temp_mt3);
			global_transform = global_transform * temp_mt4 ;
			
            break;

        case TS_LOCAL:

            // Note the order of the mult, i.e. q comes after
			qnorm.ToRotationMatrix(temp_mt3);
			temp_mt4.fromMatrix3(temp_mt3);
			global_transform = global_transform * temp_mt4 ;
           
            break;
        }
}

void Camera::roll(const Radian& angle, TransformSpace relativeTo ){

	this->rotate(Vector3::UNIT_Z, angle, relativeTo);

}

void Camera::pitch(const Radian& angle, TransformSpace relativeTo ){

	this->rotate(Vector3::UNIT_X, angle, relativeTo);
}

void Camera::yaw(const Radian& angle, TransformSpace relativeTo ){

	this->rotate(Vector3::UNIT_Y, angle, relativeTo);
}

void Camera::setOrientation(const Quaternion & orientation_value){


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
	global_transform =  temp_mt4  ;


}


void Camera::convertMatrixToFloat(){


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


void Camera::updateCamera(){

	glLoadIdentity();
	this->convertMatrixToFloat();
	glMultMatrixf(arr);
	//glMatrixMode(GL_MODELVIEW);
    //glLoadMatrixf(arr);
	//glGetFloatv(GL_MODELVIEW_MATRIX,arr2);

}

void Camera::scale(const Vector3& scale_value){

	//Vector3 sc = global_transform.getScale() + scale_value;
	//global_transform.setScale(sc);

}

void Camera::setScale(const Vector3& scale_value){

	//global_transform.setScale(scale_value);
}

Matrix3 Camera::getLocalAxes(){

	Matrix3 return_matrix;
	this->global_transform.extract3x3Matrix(return_matrix);
	return return_matrix;

}