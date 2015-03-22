#ifndef __Triangle_H
#define __Triangle_H

#include <vector>
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
using namespace std;

class Triangle
{
	private:
			
		GLfloat vertex_01[3];
		GLfloat vertex_02[3];
		GLfloat vertex_03[3];

		GLfloat color_01[3];
		GLfloat color_02[3];
		GLfloat color_03[3];

	public:

		#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX Triangle included")

		Triangle(GLfloat vertex_01[], GLfloat vertex_02[], GLfloat vertex_03[], GLfloat color_01[], GLfloat color_02[], GLfloat color_03[] );
		
		GLfloat get_vertex_01(int);
		GLfloat get_vertex_02(int);
		GLfloat get_vertex_03(int);
		GLfloat get_color_01(int);
		GLfloat get_color_02(int);
		GLfloat get_color_03(int);

};

#endif