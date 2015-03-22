#define NO_SDL_GLEXT
#include <GL\glew.h>
#include "Material.h"
#include "MaterialManager.h"
#include "SceneManager.h"

Material::Material(const std::string name){

	material_name = name;
	m_diffuse[0] = 1.0;
	m_diffuse[1] = 0.0;
	m_diffuse[2] = 0.0;
	m_diffuse[3] = 1.0;
	m_specular[0] = 0.8;
	m_specular[1] = 0.8;
	m_specular[2] = 0.8;
	m_specular[3] = 1.0;
	m_ambient[0] = 0.3;
	m_ambient[1] = 0.3;
	m_ambient[2] = 0.3;
	m_ambient[3] = 1.0;
	m_shine[0] = 110.0;
	m_program = MaterialManager::getInstance()->getDefaultMaterialProgram();
	m_numbers_lights = 0;
	m_texture = NULL;
	
	/*m_lights_outer_anagles[0] = 36;
	m_lights_outer_anagles[1] = 36;
	m_lights_outer_anagles[2] = 36;
	m_lights_outer_anagles[3] = 36;
	m_lights_outer_anagles[4] = 36;
	m_lights_outer_anagles[5] = 36;
	m_lights_outer_anagles[6] = 36;
	m_lights_outer_anagles[7] = 36;*/
}

std::string Material::getName(){

	return material_name;

}

void Material::setAmbientColour(float red, float green, float blue){

	m_ambient[0] = red;
	m_ambient[1] = green;
	m_ambient[2] = blue;

}

void Material::setDiffiuseColour(float red, float green, float blue){

	m_diffuse[0] = red;
	m_diffuse[1] = green;
	m_diffuse[2] = blue;

}

void Material::setShineValue(float val){

	m_shine[0] = val;

}

void Material::setSpecularColour(float red, float green, float blue){

	m_specular[0] = red;
	m_specular[1] = green;
	m_specular[2] = blue;

}

void Material::setTexture2D( Texture2D * tex){
	
	m_texture = tex->getTexture();

}

void Material::enableMaterial(){

	glUseProgram(m_program);
	float type;

	m_numbers_lights = SceneManager::getInstance()->getLightsNumber();
	std::list <Light*> sc_lt = SceneManager::getInstance()->getSceneLights();
	std::list <Light*>::iterator sc_lt_it;
	int i = 0;
	for (sc_lt_it = sc_lt.begin(); sc_lt_it != sc_lt.end(); ++sc_lt_it){
	
		m_lights_outer_anagles[i] = (**sc_lt_it).getSpotlightOuterAngle();
		if (i == 0){
			
			type = (**sc_lt_it).getType();
		
		}

		i++;
	
	}

	//std::cout << m_lights_outer_anagles[0] << std::endl;

	GLint val = glGetUniformLocation(m_program, "diffuseVal");
	glUniform4f(val,m_diffuse[0],m_diffuse[1],m_diffuse[2],m_diffuse[3]);

	GLint val2 = glGetUniformLocation(m_program, "specularVal");
	glUniform4f(val2,m_specular[0],m_specular[1],m_specular[2],m_specular[3]);

	GLint val3 = glGetUniformLocation(m_program, "ambientVal");
	glUniform4f(val3,m_ambient[0],m_ambient[1],m_ambient[2],m_ambient[3]);

	GLint val4 = glGetUniformLocation(m_program, "shine");
	glUniform1f(val4,m_shine[0]);

	GLint val5 = glGetUniformLocation(m_program, "cos_outer_cone_angle");
	glUniform1fv(val5,8,m_lights_outer_anagles);

	GLint val6 = glGetUniformLocation(m_program, "number_lights_uniform");
	int s = m_numbers_lights -1;
	glUniform1f(val6,s);

	glActiveTexture(GL_TEXTURE0);
	GLint val7 = glGetUniformLocation(m_program, "tex");
	glUniform1i(val7,0);
	glBindTexture(GL_TEXTURE_2D,m_texture);
	//SceneManager::getInstance()->getSceneLights(lt);
	//int i = lt[0].getType();
	//std::cout<<type<<std::endl;
	GLint val8 = glGetUniformLocation(m_program, "type_uniform");
	glUniform1f(val8,type);

}

void Material::disableMaterial(){

	glUseProgram(0);

}