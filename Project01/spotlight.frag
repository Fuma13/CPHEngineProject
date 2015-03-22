
varying vec4 diffuse[2];
varying vec4 ambientGlobal; 
varying vec4 ambient[2]; 
varying vec4 specular[2];
varying vec3 normal;
varying vec3 lightDir[2];
varying vec3 lightDir2[2];
varying vec3 halfVector[2];
varying float dist[2];

uniform float cos_outer_cone_angle [8];  // 36 degrees
uniform float shine;
uniform sampler2D tex;
varying float type;
varying int number_lights;

void main()
{
	//float type = 0;
	vec3 n,halfV,viewV,ldir;
	float NdotL,NdotHV;
	vec4 color = ambientGlobal;
	float att;
	int c = number_lights + 1;
	vec4 texture_color = texture2D(tex,gl_TexCoord[0].st);

	for (int l = 0; l<c;l++){
	
		if (type == 2){

		vec3 L = normalize(lightDir[l]);
		//vec3 L = vec3(0.0,1.0,0.0);
		vec3 D = normalize(gl_LightSource[l].spotDirection);
	

		float cos_cur_angle = dot(-L, D);
	
	
		float cos_inner_cone_angle = gl_LightSource[l].spotCosCutoff;
	
		float cos_inner_minus_outer_angle = cos_inner_cone_angle - cos_outer_cone_angle[l];

		
		if (cos_cur_angle > cos_inner_cone_angle) {
	
			// a fragment shader can't write a verying variable, hence we need
			// a new variable to store the normalized interpolated normal 
	
			n = normalize(normal);
	
			// compute the dot product between normal and ldir 
			NdotL = max(dot(n,normalize(lightDir[l])),0.0);

	
			att = 1.0/((pow(dist[l],2)) / gl_LightSource[l].quadraticAttenuation);
			color += att * (diffuse[l] * NdotL + ambient[l] + texture_color);
	
			
			halfV = normalize(halfVector[l]);
			NdotHV = max(dot(n,halfV),0.0);
			color += att * specular[l] * pow(NdotHV,shine);
			

		
		}
		
		else if( cos_cur_angle > cos_outer_cone_angle[l] )
		{
			float falloff = (cos_cur_angle - cos_outer_cone_angle[l]) / cos_inner_minus_outer_angle;
		
			n = normalize(normal);
	
	
			NdotL = max(dot(n,normalize(lightDir[l])),0.0);

			att = 1.0/((pow(dist[l],2)) / gl_LightSource[l].quadraticAttenuation);
			color += att * (diffuse[l] * NdotL + ambient[l] + texture_color) * falloff;
	
		
			halfV = normalize(halfVector[l]);
			NdotHV = max(dot(n,halfV),0.0);
			color += att * specular[l] * pow(NdotHV,shine) * falloff;
			
		}

		}
		else if (type == 0){
		
	
			// a fragment shader can't write a verying variable, hence we need
			// a new variable to store the normalized interpolated normal 
	
			n = normalize(normal);
	
			// compute the dot product between normal and ldir 
			NdotL = max(dot(n,normalize(lightDir[l])),0.0);

	
			att = 1.0/((pow(dist[l],2)) / gl_LightSource[l].quadraticAttenuation);
			color += att * (diffuse[l] * NdotL + ambient[l] + texture_color);
	
			
			halfV = normalize(halfVector[l]);
			NdotHV = max(dot(n,halfV),0.0);
			color += att * specular[l] * pow(NdotHV,shine);
		
		
		}

		else if (type == 1){
		
	
			// a fragment shader can't write a verying variable, hence we need
			// a new variable to store the normalized interpolated normal 
	
			n = normalize(normal);
	
			// compute the dot product between normal and ldir 
			NdotL = max(dot(n,normalize(lightDir2[l])),0.0);

			//if (NdotL > 0.0) {

			//att = 1.0/((pow(dist[l],2)) / gl_LightSource[l].quadraticAttenuation);
			color +=  (diffuse[l] * NdotL + ambient[l] + texture_color);
	
			
			halfV = normalize(halfVector[l]);
			NdotHV = max(dot(n,halfV),0.0);
			color +=  specular[l] * pow(NdotHV,shine);
		//}
		
		}
	}

	
	//gl_FragColor = texture_color;
	gl_FragColor = color;
}