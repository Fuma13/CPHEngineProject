
uniform vec4 diffuseVal, ambientVal, specularVal;
varying vec4 diffuse[2]; //these arrays should be 8 dimension, but seems glsl doesn't work with arrays bigger than 3 dim 
varying vec4 ambientGlobal;
varying vec4 ambient[2];
varying vec4 specular[2];
varying vec3 normal;
varying vec3 lightDir[2];
varying vec3 lightDir2[2];
varying vec3 halfVector[2];
varying float dist[2];
varying float type;
uniform float type_uniform;

uniform int number_lights_uniform;
varying int number_lights;

void main()
{	
	vec4 ecPos;
	vec3 aux;
	number_lights = 0; //number_lights_uniform;
	type = type_uniform;
	int s = number_lights + 1;
	gl_TexCoord[0] = gl_MultiTexCoord0;

	/* first transform the normal into eye space and normalize the result */
	normal = normalize(gl_NormalMatrix * gl_Normal);
	
	ecPos = gl_ModelViewMatrix * gl_Vertex;
	for (int i = 0;i<s;i++){

		
		aux = vec3(gl_LightSource[i].position-ecPos);
		lightDir[i] = normalize(aux);
		lightDir2[i] = normalize(gl_LightSource[0].spotDirection );
		
		
	
		/* compute the distance to the light source to a varying variable*/
		dist[i] = length(aux);

		/* Normalize the halfVector to pass it to the fragment shader */
		halfVector[i] = normalize(gl_LightSource[i].halfVector.xyz);
	
		/* Compute the diffuse, ambient, globalAmbient, specular terms */
		diffuse[i] = diffuseVal * gl_LightSource[i].diffuse;
		ambient[i] = ambientVal * gl_LightSource[i].ambient;
		specular[i] = specularVal * gl_LightSource[i].specular;
	
	}
	ambientGlobal = gl_LightModel.ambient * ambientVal;
	gl_Position = ftransform();
	
	
	
	
	
} 
