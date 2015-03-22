#ifndef  __Light_H__
#define  __Light_H__


#include "Vector3.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
//#include "MovableObject.h"
//#include "TransformNode.h"


class Light
{

	public:
		#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX Light included")



		// Defines the type of light
        enum LightTypes
        {
            // Point light sources give off light equally in all directions, so require only position not direction
            LT_POINT = 0,
            // Directional lights simulate parallel light beams from a distant source, hence have direction but no position
            LT_DIRECTIONAL = 1,
            // Spotlights simulate a cone of light from a source so require position and direction, plus extra values for falloff
            LT_SPOTLIGHT = 2
        };

		//Light();
		// Normal constructor. Should not be called directly, but rather the SceneManager::createLight method should be used.
        Light(const std::string  & name, LightTypes type);

		// Standard destructor.
        ~Light();

		// Sets the type of light - see LightTypes for more info.
        void setType(LightTypes type);

        // Returns the light type.
        LightTypes getType(void) const;

        void setPosition( Vector3& vec);

        Vector3& getPosition(void) ;

        void setDirection(const Vector3& vec);

        const Vector3& getDirection(void) const;

        void setDiffuseColour(float red, float green, float blue);

        void setSpecularColour(float red, float green, float blue);

		void setAmbientColour(float red, float green, float blue);

        void setAttenuation(float quadratic);

        float getAttenuation(void) ;

        float getSpotlightInnerAngle(void);

        float getSpotlightOuterAngle(void);

		void setSpotlightInnerAngle(float val);

		void setSpotlightOuterAngle(float val);

		void setNumberGlLight ( GLenum gl_light);

		void updadeLight(void);

		std::string getName(void);


	
protected:
		

		// Variables
		std::string light_name;
		LightTypes m_light_type;
		float  m_position[4];
		float m_direction [3];
		float m_diffuse [4];
		float m_specular [4];
		float m_ambient[4];
		float m_attenuation[1];
		float m_spot_inner[1];
		float m_spot_outer[1];
		GLenum number_gl_light;
		
};


#endif