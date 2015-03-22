#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__

//#include <stdlib.h>
#include <stdio.h>

#include "SDL.h"
#include "SDL_opengl.h"

class Texture2D
{
	friend class ResourceManager;

	public:
		GLuint getTexture();
		int getWidth();
		int getHeight();
		~Texture2D();

	private:
		Texture2D();

		GLuint m_texture;
		int m_width;
		int m_height;

		GLuint loadTexture( const char * filename, int width, int height );
};

#endif