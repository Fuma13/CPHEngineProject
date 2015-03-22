#ifndef __RenderManager_H
#define __RenderManager_H

#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include <gl\gl.h>                         // Header File For The OpenGL32 Library
#include <gl\glu.h>                            // Header File For The GLu32 Library
//#include "GL\glew.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP     16

using namespace std;

class RenderManager
{
private:
	static RenderManager * m_instance;
	~RenderManager();
	/*texture*/
	static const int size = 1;
	GLuint texture[size];

protected:

	RenderManager();
public:
	static RenderManager * getInstance ();	
	/*Provisory init for the whole engine*/
	
	
	int initializeRender();

	void Quit( int returnCode );

	//Texture function
	int LoadGLTextures(char*, int);
	GLuint getTexture(int);


};

#endif