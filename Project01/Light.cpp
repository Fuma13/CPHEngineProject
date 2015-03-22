#include "Light.h"




Light::Light(const std::string  & name, LightTypes type)
{
		light_name = name;
		m_light_type = type;
		m_position[0] = 0.0;
		m_position[1] = 0.0;
		m_position[2] = 0.0;
		m_position[3] = 1.0;
		m_direction[0] = 0.0;
		m_direction[1] = 0.0;
		m_direction[2] = -1.0;
		m_diffuse[0] = 0.8;
		m_diffuse[1] = 0.8;
		m_diffuse[2] = 0.8;
		m_diffuse[3] = 1.0;
		m_specular[0] = 0.8;
		m_specular[1] = 0.8;
		m_specular[2] = 0.8;
		m_specular[3] = 1.0;
		m_ambient[0] = 0.1;
		m_ambient[1] = 0.1;
		m_ambient[2] = 0.1;
		m_ambient[3] = 1.0;
		m_attenuation[0] = 8.0;
		m_spot_inner[0] = 0.8f;
		m_spot_outer[0] = 0.8f;
	
		
}


Light::~Light()
{

}

void Light::setType(LightTypes type)
{
        m_light_type = type;
}

Light::LightTypes Light::getType(void) const
{
        return m_light_type;
}



void Light::setPosition( Vector3& vec)
{
	m_position[0] = vec.x;
	m_position[1] = vec.y;
	m_position[2] = vec.z;
	//std::cout << m_position[2] << std::endl;
	
	//glLightfv(this->number_gl_light, GL_POSITION, m_position);

}

Vector3& Light::getPosition(void) 
{
	return Vector3(m_position[0],m_position[1],m_position[2]);
		
}



void Light::setDirection(const Vector3& vec)
{
     
	m_direction[0] = vec.x;
	m_direction[1] = vec.y;
	m_direction[2] = vec.z;
	//glLightfv(this->number_gl_light, GL_SPOT_DIRECTION, m_direction);
}

const Vector3& Light::getDirection(void) const
{
        return Vector3(m_direction[0],m_direction[1],m_direction[2]);
}

void Light::setDiffuseColour(float red, float green, float blue)
{
        m_diffuse[0] = red;
        m_diffuse[1] = green;
        m_diffuse[2] = blue;
		glLightfv(this->number_gl_light, GL_DIFFUSE, m_diffuse);
}

void Light::setSpecularColour(float red, float green, float blue)
{
        m_specular[0] = red;
        m_specular[1] = green;
        m_specular[2] = blue;
		glLightfv(this->number_gl_light, GL_SPECULAR, m_specular);
}

void Light::setAmbientColour(float red, float green, float blue)
{

	m_ambient[0] = red;
	m_ambient[1] = green;
	m_ambient[2] = blue;
	glLightfv(this->number_gl_light, GL_AMBIENT, m_ambient);

}

void Light::setAttenuation(float quadratic)
{

        m_attenuation[0] = quadratic;
		glLightfv(this->number_gl_light,GL_QUADRATIC_ATTENUATION,m_attenuation);
}



float Light::getAttenuation(void)
    
{
     return m_attenuation[0];
}




void Light::setSpotlightInnerAngle(float val)
{
		m_spot_inner[0] = val;
		glLightfv(this->number_gl_light,GL_SPOT_CUTOFF, m_spot_inner);
}

void Light::setSpotlightOuterAngle(float val)
	{
		m_spot_outer[0] = val;
	}



float Light::getSpotlightInnerAngle(void) 
{
        return m_spot_inner[0];
}

float Light::getSpotlightOuterAngle(void)
{
        return m_spot_outer[0];
}

void Light::setNumberGlLight(GLenum gl_light){

	number_gl_light = gl_light;

	glLightfv(this->number_gl_light, GL_POSITION, m_position);
	glLightfv(this->number_gl_light, GL_SPOT_DIRECTION, m_direction);
	glLightfv(this->number_gl_light, GL_DIFFUSE, m_diffuse);
	glLightfv(this->number_gl_light, GL_SPECULAR, m_specular);
	glLightfv(this->number_gl_light, GL_AMBIENT, m_ambient);
	glLightfv(this->number_gl_light,GL_QUADRATIC_ATTENUATION,m_attenuation);
	glLightfv(this->number_gl_light,GL_SPOT_CUTOFF, m_spot_inner);

}

void Light::updadeLight(){

	//float temp_pos[] = {0.0,0.0,8.0,1.0};
	//float temp_dir[] = {0.0,0.0,-1.0};
	//std::cout << m_position[2] << std::endl;
	
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, m_position /*temp_pos*/);
	glPopMatrix();
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,m_direction /*temp_dir*/);
	glPopMatrix();

}

std::string Light::getName(){


	return light_name;
}