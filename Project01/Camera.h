#ifndef __Camera_H__
#define __Camera_H__

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include <list>
#include <string>
#include "Mesh.h"
#include "Math.h"
#include "Vector3.h"
#include "Node.h"
#include "MovableObject.h"
#include "Matrix3.h"


class Camera : public MovableObject{

	public:

		#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX Camera included")

		Camera (const std::string  & stringName);
		std::string getName();
		void updateCamera();

		const Quaternion & getOrientation()  ;
		const Vector3 & getScale() ;
		const Vector3 & getPosition() ;
		void translate (const Vector3& translation_value, TransformSpace relativeTo);
		void setPosition(const Vector3& position_value);
		void rotate(const Vector3& axis, const Radian& angle, TransformSpace relativeTo);
		void rotate(const Quaternion& rotation_value, TransformSpace relativeTo);
		void roll(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);
        void pitch(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);
        void yaw(const Radian& angle, TransformSpace relativeTo = TS_LOCAL);
		void setOrientation(const Quaternion & orientation_value);
		void scale(const Vector3& scale_value);
		void setScale(const Vector3& scale_value);
		Matrix3 getLocalAxes();
		


	protected:

		Matrix4 global_transform;
		GLfloat arr[16];
		Matrix4 getParentTransform() ;
		void convertMatrixToFloat();
		std::string camera_name;

};


#endif
