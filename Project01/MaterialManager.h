#ifndef __MATERIALMANAGER_H__
#define __MATERIALMANAGER_H__

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include <list>
#include <string>
#include "Vector3.h"
#include "textfile.h"

class MaterialManager{

	public:

		static MaterialManager * getInstance();
		void enableDefaultMaterial();
		GLuint getDefaultMaterialProgram();

	protected:

		MaterialManager();
		GLuint vertex_default_material,fragment_default_material,program_default_material;
			
	private:

		static MaterialManager * p_instance;

};

#endif