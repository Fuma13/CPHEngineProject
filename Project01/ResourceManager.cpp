#define NO_SDL_GLEXT
#include <GL\glew.h>

#include "ResourceManager.h"

ResourceManager * ResourceManager::p_instance = NULL;

ResourceManager * ResourceManager::getInstance()
{
	if(p_instance == NULL){
	
		p_instance = new ResourceManager();

	}

	return p_instance;
}

ResourceManager::ResourceManager()
{
	mesh_tab.clear();
}

Mesh* ResourceManager::loadMesh(const std::string& mesh_file)
{
	std::map<std::string, Mesh *>::iterator iter;
	iter = mesh_tab.find(mesh_file);
	Mesh* contenitor_mesh;
	std::list<Mesh *> mesh_list;

	if((iter) == mesh_tab.cend())
	{
		if (!Import3DFromFile(mesh_file))
		{	//error
			return false;
		}

		if(scene->HasMeshes())
		{
			contenitor_mesh = new Mesh(mesh_file);
			if(scene->mNumMeshes==1)
			{
				convertAIMeshToContenitorMesh(contenitor_mesh, scene->mMeshes[0]);
			}
			else
			{
				for(unsigned int n = 0; n < scene->mNumMeshes; ++n)
				{
					Mesh* sub_mesh = convertAIMeshToMesh(scene->mMeshes[n]);
					contenitor_mesh->addSubMesh(sub_mesh);
				}
			}
			mesh_tab.insert(std::pair<std::string,Mesh *>(mesh_file,contenitor_mesh));
			
			//OK
			return contenitor_mesh;
			
		}
		else
		{	//error
			return false;
		}
		
	}
	else
	{	//OK
		Mesh* mesh_new = (iter->second)->returnCopy();
		return mesh_new;
	}

}

bool ResourceManager::Import3DFromFile(const std::string& pFile)
{
	//check if file exists
	std::ifstream fin(pFile.c_str());
	if(!fin.fail()) {
		fin.close();
	}
	else{
		printf("Couldn't open file: %s\n", pFile);
		printf("%s\n", importer.GetErrorString());
		return false;
	}

	scene = importer.ReadFile( pFile, aiProcessPreset_TargetRealtime_Quality |aiProcess_Triangulate | aiProcess_GenSmoothNormals /*|aiProcess_GenUVCoords*/);

	// If the import failed, report it
	if( !scene)
	{
		printf("%s\n", importer.GetErrorString());
		return false;
	}

	// Now we can access the file's contents.
	printf("Import of scene %s succeeded.",pFile.c_str());

	//importNameSubMesh(pFile);

	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}

Mesh* ResourceManager::convertAIMeshToMesh(aiMesh* ai_mesh)
{
	std::string temp_name;
	for(int i=0; i<ai_mesh->mName.length; i++)
		temp_name += ai_mesh->mName.data[i];

	Mesh* mesh_rtn = new Mesh(temp_name);

	mesh_rtn->m_num_vertices = ai_mesh->mNumVertices;
	mesh_rtn->m_vertices = new Vector3[mesh_rtn->m_num_vertices];
	mesh_rtn->m_normals = new Vector3[mesh_rtn->m_num_vertices];
	mesh_rtn->m_binormals = new Vector3[mesh_rtn->m_num_vertices];
	mesh_rtn->m_tangents = new Vector3[mesh_rtn->m_num_vertices];
	mesh_rtn->m_texture_coord = new float[(mesh_rtn->m_num_vertices)*2];
	for (unsigned int i = 0 ; i < ai_mesh->mNumVertices ; i++) 
	{
		if(ai_mesh->HasPositions())
		{
			//Vector
			const aiVector3D* pPos      = &(ai_mesh->mVertices[i]);
			mesh_rtn->m_vertices[i].x = pPos->x;
			mesh_rtn->m_vertices[i].y = pPos->y;
			mesh_rtn->m_vertices[i].z = pPos->z;
		}
		
		if(ai_mesh->HasNormals())
		{
			//Normals
			const aiVector3D* pNor      = &(ai_mesh->mNormals[i]);
			mesh_rtn->m_normals[i].x = pNor->x;
			mesh_rtn->m_normals[i].y = pNor->y;
			mesh_rtn->m_normals[i].z = pNor->z;
		}

		if(ai_mesh->HasTangentsAndBitangents())
		{
			//Bitangent - Binormal
			const aiVector3D* pBin      = &(ai_mesh->mBitangents[i]);
			mesh_rtn->m_binormals[i].x = pBin->x;
			mesh_rtn->m_binormals[i].y = pBin->y;
			mesh_rtn->m_binormals[i].z = pBin->z;

			//Tangent
			const aiVector3D* pTan      = &(ai_mesh->mTangents[i]);
			mesh_rtn->m_tangents[i].x = pTan->x;
			mesh_rtn->m_tangents[i].y = pTan->y;
			mesh_rtn->m_tangents[i].z = pTan->z;
		}
		
		if(ai_mesh->HasTextureCoords(i))
		{
			//Texture Coordinates
			//const aiVector3D* pTex		= (ai_mesh->mTextureCoords[i]);
			/*mesh_rtn->m_texture_coord[i].x = ai_mesh->mTextureCoords[0][i].x;
			mesh_rtn->m_texture_coord[i].y = ai_mesh->mTextureCoords[0][i].y;*/
			//mesh_rtn->m_texture_coord[i].z = pTex->z;
			mesh_rtn->m_texture_coord[i*2] = ai_mesh->mTextureCoords[0][i].x;
			mesh_rtn->m_texture_coord[i*2+1] = ai_mesh->mTextureCoords[0][i].y;
		}
	}

	//Index
	mesh_rtn->m_num_indices = ai_mesh->mNumFaces*3;
	mesh_rtn->m_num_faces = ai_mesh->mNumFaces;
	mesh_rtn->m_indices = new unsigned int[mesh_rtn->m_num_indices];
	int k=0;
	if(ai_mesh->HasFaces())
	{
		for (unsigned int i = 0 ; i < ai_mesh->mNumFaces ; i++) 
		{
			const aiFace& Face = ai_mesh->mFaces[i];
			mesh_rtn->m_indices[k] = Face.mIndices[0];
			mesh_rtn->m_indices[k+1] = Face.mIndices[1];
			mesh_rtn->m_indices[k+2] = Face.mIndices[2];
			k+=3;
		}
	}


	mesh_rtn->initBuffer();

	return mesh_rtn;
}

void ResourceManager::convertAIMeshToContenitorMesh(Mesh* mesh, aiMesh* ai_mesh)
{
	mesh->m_num_vertices = ai_mesh->mNumVertices;
	mesh->m_vertices = new Vector3[mesh->m_num_vertices];
	mesh->m_normals = new Vector3[mesh->m_num_vertices];
	mesh->m_binormals = new Vector3[mesh->m_num_vertices];
	mesh->m_tangents = new Vector3[mesh->m_num_vertices];
	mesh->m_texture_coord = new float[mesh->m_num_vertices];
	for (unsigned int i = 0 ; i < ai_mesh->mNumVertices ; i++) 
	{
		
		if(ai_mesh->HasPositions())
		{
			//Vertices
			const aiVector3D* pPos      = &(ai_mesh->mVertices[i]);
			mesh->m_vertices[i].x = pPos->x;
			mesh->m_vertices[i].y = pPos->y;
			mesh->m_vertices[i].z = pPos->z;
		}
		
		if(ai_mesh->HasNormals())
		{
			//Normal
			const aiVector3D* pNor      = &(ai_mesh->mNormals[i]);
			mesh->m_normals[i].x = pNor->x;
			mesh->m_normals[i].y = pNor->y;
			mesh->m_normals[i].z = pNor->z;
		}

		if(ai_mesh->HasTangentsAndBitangents())
		{
			//Bitangent - Binormal
			const aiVector3D* pBin      = &(ai_mesh->mBitangents[i]);
			mesh->m_binormals[i].x = pBin->x;
			mesh->m_binormals[i].y = pBin->y;
			mesh->m_binormals[i].z = pBin->z;

			//Tangent
			const aiVector3D* pTan      = &(ai_mesh->mTangents[i]);
			mesh->m_tangents[i].x = pTan->x;
			mesh->m_tangents[i].y = pTan->y;
			mesh->m_tangents[i].z = pTan->z;
		}
		
		if(ai_mesh->HasTextureCoords(i))
		{
			//Texture Coordinates
			//const aiVector3D* pTex		= (ai_mesh->mTextureCoords[i]);
			//mesh->m_texture_coord[i].x = ai_mesh->mTextureCoords[0][i].x;
			//mesh->m_texture_coord[i].y = ai_mesh->mTextureCoords[0][i].y;
			//mesh->m_texture_coord[i].z = pTex->z;
			mesh->m_texture_coord[i*2] = ai_mesh->mTextureCoords[0][i].x;
			mesh->m_texture_coord[i*2+1] = ai_mesh->mTextureCoords[0][i].y;
		}
	}

	//Index
	mesh->m_num_indices = ai_mesh->mNumFaces*3;
	mesh->m_num_faces = ai_mesh->mNumFaces;
	mesh->m_indices = new unsigned int[mesh->m_num_indices];
	int k=0;
	if(ai_mesh->HasFaces())
	{
		for (unsigned int i = 0 ; i < ai_mesh->mNumFaces ; i++) 
		{
			const aiFace& Face = ai_mesh->mFaces[i];
			mesh->m_indices[k] = Face.mIndices[0];
			mesh->m_indices[k+1] = Face.mIndices[1];
			mesh->m_indices[k+2] = Face.mIndices[2];
			k+=3;
		}
	}

	mesh->initBuffer();
}

Texture2D* ResourceManager::loadTexture( const char * filename, int width, int height )
{
	std::map<const char * , Texture2D *>::iterator iter;
	iter = texture_tab.find(filename);

	if((iter) == texture_tab.cend())
	{
		Texture2D* text = new Texture2D();
		text->m_texture = text->loadTexture(filename,width, height);
		if(text->m_texture == 0)
		{
			//error
			printf("ERROR:Import of Texture %s failed.",filename);
		}
		else
		{
			// Imported correctly
			printf("Import of Texture %s succeeded.",filename);
			texture_tab.insert(std::pair<const char *,Texture2D *>(filename,text));
			return text;
		}
	}
	else
	{
		return iter->second;
	}
}