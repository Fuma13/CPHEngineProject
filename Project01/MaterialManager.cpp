#define NO_SDL_GLEXT
#include <GL\glew.h>
#include "MaterialManager.h"

MaterialManager::MaterialManager(){
	
}

MaterialManager * MaterialManager::p_instance = NULL;

MaterialManager * MaterialManager::getInstance(){

	if(p_instance == NULL){
	
		p_instance = new MaterialManager();
	}

	return p_instance;

}

void MaterialManager::enableDefaultMaterial(){


char *vs = NULL,*fs = NULL,*fs2 = NULL;

	vertex_default_material = glCreateShader(GL_VERTEX_SHADER);
	fragment_default_material = glCreateShader(GL_FRAGMENT_SHADER);
	//f2 = glCreateShader(GL_FRAGMENT_SHADER);


	vs = textFileRead("spotlight.vert");
	fs = textFileRead("spotlight.frag");
	//fs2 = textFileRead("toon2.frag");

	const char * ff = fs;
	//const char * ff2 = fs2;
	const char * vv = vs;

	glShaderSource(vertex_default_material, 1, &vv,NULL);
	glShaderSource(fragment_default_material, 1, &ff,NULL);


	free(vs);free(fs);

	glCompileShader(vertex_default_material);
	glCompileShader(fragment_default_material);

	program_default_material = glCreateProgram();
	glAttachShader(program_default_material,fragment_default_material);
	glAttachShader(program_default_material,vertex_default_material);

	glLinkProgram(program_default_material);
	//glUseProgram(program_default_material);

}

GLuint MaterialManager::getDefaultMaterialProgram(){

	return program_default_material;

}
