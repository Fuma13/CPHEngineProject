#ifndef __GamePlay_02_H__
#define __GamePlay_02_H__

#include "GameState.h"
#include "CubeObjectTest.h"
#include <string>
#include "SceneManager.h"
#include "MaterialManager.h"
#include "Light.h"
#include "Material.h"
#include "Texture2D.h"
//class SceneManager;
//class Vector2;
//class Camera;
class GameObject;

using namespace std;

#pragma once

// You could also call this our first level
class GamePlay_02 : public GameState
{
private:

		//Camera testing
		float speed;
		float x_vel;
		float y_vel;
		float x_vel_li;
		float y_vel_li;
		float xrot;
		float yrot;
		float xrot_zero;
		float currentFramePositionx;
		float lastFramePositionx;
		float yrot_zero;
		float currentFramePositiony;
		float lastFramePositiony;

		// ONLY FOR TESTING
		TransformNode * node1 ;
		TransformNode * node4 ;
		TransformNode * node2 ;
		TransformNode * node3 ;
		TransformNode * node5 ;
		float translate_ratio;
		GLfloat stam_arr[16];
		Mesh * cube ;
		Mesh * cube2;
		Camera * cam;
		Vector2 pos;
		int posx, posy;

		Light * light2;
		Material * mat05;

		MaterialManager * mat_manager;
		//end
		
		CubeObjectTest newAgeCube;

		static GamePlay_02 * m_instance;
		~GamePlay_02();

		string name;

		

	protected:
		GamePlay_02();
public:

		
		CubeObjectTest * cube_01;
		CubeObjectTest * cube_02;
		CubeObjectTest * cube_03;
		CubeObjectTest * cube_04;

		#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX GamePlay_01 included")
		
		string get_name();
		
		static GamePlay_02 * getInstance ();
		
		void init();
		void destroy();
		bool update(vector<Event*> events);

		void spawnGameObject(GameObject* game_obj, Vector3 position, Quaternion orientation){};
		void spawnGameObject(EGameObject type, Vector3 position, Quaternion orientation){};

};
#endif
