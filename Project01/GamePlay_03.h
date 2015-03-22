#ifndef __GamePlay_03_H__
#define __GamePlay_03_H__

#include "GameState.h"
#include "PlayerCar.h"
#include "AICar.h"
#include "CubeObjectTest.h"
#include <string>
#include "SceneManager.h"
#include "Material.h"
#include "Light.h"
//class SceneManager;
//class Vector2;
//class Camera;
class GameObject;


using namespace std;

#pragma once

// You could also call this our first level
class GamePlay_03 : public GameState
{
private:

		//Camera testing
		float speed;
		float x_vel;
		float y_vel;
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
		//end

		//level assets
		PlayerCar * playerCar;
		AICar* car;
		AICar* car2;
		Material * mat_02;
		Material * mat_03;
		Light * light3;

		static GamePlay_03 * m_instance;
		~GamePlay_03();

		string name;

	protected:
		GamePlay_03();
public:


		#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX GamePlay_03 included")
		
		string get_name();
		
		static GamePlay_03 * getInstance ();
		
		void init();
		void destroy();
		bool update(vector<Event*> events);

		void spawnGameObject(GameObject* game_obj, Vector3 position, Quaternion orientation){};
		void spawnGameObject(EGameObject type, Vector3 position, Quaternion orientation){};

};
#endif
