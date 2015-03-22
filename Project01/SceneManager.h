#ifndef __SceneManager_H__
#define __SceneManager_H__

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include <list>
#include <string>
#include "Mesh.h"
class RootTransformNode;
#include "Camera.h"
#include "TransformNode.h"
#include "RootTransformNode.h"
//#include <gl\gl.h>                         // Header File For The OpenGL32 Library
//#include <gl\glu.h>                            // Header File For The GLu32 Library
#include <Windows.h>
#include <wchar.h>
#include "Vector2.h"
#include "Light.h"

class Root;



class SceneManager
{

	public:

		//Root * m_Root;

		static SceneManager * getInstance ();
		TransformNode * getRootTransformNode();
		Camera * createCamera(const std::string  & stringName);

		void destroyCamera(const std::string  & stringName);
		
		void renderScene();

		Light * createLight(const std::string  & name, Light::LightTypes type);


		std::list <Light*> getSceneLights();

		int getLightsNumber(void);

		~SceneManager();//{/*delete this;*/}

		//Texture function
		//int LoadGLTextures(char*, int);
		//GLuint getTexture(int);
	
		//FT
		/*Provisory init for the whole engine*/
		//int initializeEngine();
		//void Quit( int returnCode );


	protected:

		SceneManager();
		TransformNode * root_ptr;
		std::list <Camera*> camera_list;
		//Light  scene_lights[8] ;
		std::list <Light*> scene_lights;
		int number_scene_lights;

	private:

		static SceneManager * p_instance;
		/*texture*/
		//static const int size = 1;
		//GLuint texture[size];

		// ONLY FOR TESTING
		float translate_ratio;
		Vector2 pos;
};
#endif
