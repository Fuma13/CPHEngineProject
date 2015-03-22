#ifndef __RootTransformNode_H__
#define __RootTransformNode_H__

#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_opengl.h"
#include <list>
#include <string>
#include "Mesh.h"
#include "TransformNode.h"


class RootTransformNode : public TransformNode{


	public:

		#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX RootTransformNode included")

		//RootTransformNode(const std::string & stringName,float x,float y,float z);
		static RootTransformNode * getInstance(const std::string & stringName,Vector3 initial_position = Vector3::ZERO);
		~RootTransformNode(){delete this;}
	protected:

		RootTransformNode(const std::string & stringName,Vector3 initial_position = Vector3::ZERO);

	private:

		static RootTransformNode * p_instance;
};

#endif