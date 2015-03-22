#ifndef __Mesh_H__
#define __Mesh_H__

#pragma once
#include "SDL.h"
#include "SDL_opengl.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"
#include <string>
#include <map>
#include <vector>
#include "Material.h"


class Mesh
{
	friend class ResourceManager;

	//New version
	public:
		void renderMesh();
		void renderMeshDirect();
		bool hasSubMesh();
		Vector3* getVertices();
		Vector3* getNormals();
		Vector3* getTangents();
		Vector3* getBinormals();
		unsigned int getNumVertices();
		Mesh* returnCopy();

		std::map<std::string, Mesh *> sub_mesh_tab;

		void setMaterial(Material * mat);
		Material * getMaterial(void);


	private:
		Mesh(std::string name);
		~Mesh();
		void addSubMesh(Mesh* sub_mesh);
		void initBuffer();
		Material * m_material;
		

		//Only Contenitor variables

		//SubMesh variables
		GLuint vector_buffer_obj;
		GLuint index_buffer;
		GLuint normal_buffer;
		GLuint binormal_buffer;
		GLuint tangent_buffer;
		GLuint texture_coord_buffer;

		GLuint tangents_attrib_array;
		GLuint binormals_attrib_array;
		GLuint texture_coord_attrib_array;

		std::string m_name;
		unsigned int m_num_faces;
		unsigned int m_num_vertices;
		unsigned int m_num_indices;
		Vector3 * m_tangents;
		Vector3 * m_vertices;
		unsigned int* m_indices;
		Vector3 * m_normals;
		Vector3 * m_binormals;
		float * m_texture_coord;

		static int num_name;

		//unsigned int m_primitive_types;
		//aiBone ** m_bones;
		//Vector4 * m_colors;
		//unsigned int * face_array;
		//unsigned int m_material_index;
		//unsigned int m_num_uv_components;
		//unsigned int m_num_anim_meshes;
		//unsigned int m_num_bones;
		//aiAnimMesh ** m_anim_meshes;

		


	//old Version
		
	protected:
		float size_p;
		float red, green, blue;

	public:
		Mesh(float size,float red_,float green_,float blue_)
		{
			size_p = size;
			red = red_;
			green = green_;
			blue = blue_;
		}
		void drawCube ();
		
};


#endif