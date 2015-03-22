#define NO_SDL_GLEXT
#include <GL\glew.h>

#include "Texture2D.h"

Texture2D::Texture2D()
{
	m_texture =NULL;
}

Texture2D::~Texture2D()
{
	m_texture = NULL;
}

GLuint Texture2D::loadTexture( const char * filename, int width, int height )
{
	m_width = width;
	m_height = height;
	GLuint texture;
	unsigned char * data;
	FILE * file;
    
	//The following code will read in our RAW file
	file = fopen( filename, "rb" );
	if ( file == NULL ) return 0;
	data = (unsigned char *)malloc( width * height * 3 );
	fread( data, width * height * 3, 1, file );
	fclose( file );
    
	glGenTextures( 1, &texture ); //generate the texture with the loaded data
	glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture to it's array
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture environment parameters
    
	//And if you go and use extensions, you can use Anisotropic filtering textures which are of an
	//even better quality, but this will do for now.
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
	//Here we are setting the parameter to repeat the texture instead of clamping the texture
	//to the edge of our shape. 
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    
	//Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	free( data ); //free the texture
    
	return texture; //return whether it was successfull

}

GLuint Texture2D::getTexture()
{
	return m_texture;
}

int Texture2D::getWidth()
{
	return m_width;
}

int Texture2D::getHeight()
{
	return m_height;
}