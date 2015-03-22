#include "SceneManager.h"
#include "Root.h"



SceneManager::SceneManager()
{
	//Root *mRoot = Systems::getInstance();
	//std::cout << "listen: " << mRoot->get_current_GameState()->name() << std::endl;
	//mRoot->gamePlay_01->loadStuff();

	//FORT TESTING ONLY
	translate_ratio = 0.0;
	pos = Vector2(0.0,0.0);

	//game_is_run=false;//by default the game is run state is set to false so the game loop doesn't start until the user start it
	//root_ptr = RootTransformNode::getInstance("Root");
	root_ptr = Root::getInstance()->mRootTransformNode;
	//scene_lights = new Light[8];
	number_scene_lights = 0;
}



SceneManager * SceneManager::p_instance = NULL;

SceneManager * SceneManager::getInstance(){

	if(p_instance == NULL){
	
		p_instance = new SceneManager();

	}

	return p_instance;

}

TransformNode * SceneManager::getRootTransformNode(){

	return root_ptr;
}

Camera * SceneManager::createCamera(const std::string  & stringName){


	Camera * cam = new Camera (stringName);
	camera_list.push_back(cam);
	cout << "length after construction" << camera_list.size() << endl;

	return cam;

}

Light * SceneManager::createLight(const std::string  & name, Light::LightTypes type){

	Light * l = new Light (name,type);

	switch (number_scene_lights)
	{

	case (0):
		glEnable(GL_LIGHT0);
		l->setNumberGlLight(GL_LIGHT0);
		break;
	case (1):
		glEnable(GL_LIGHT1);
		l->setNumberGlLight(GL_LIGHT1);
		break;
	case (2):
		glEnable(GL_LIGHT2);
		l->setNumberGlLight(GL_LIGHT2);
		break;
	case (3):
		glEnable(GL_LIGHT3);
		l->setNumberGlLight(GL_LIGHT3);
		break;
	case (4):
		glEnable(GL_LIGHT4);
		l->setNumberGlLight(GL_LIGHT4);
		break;
	case (5):
		glEnable(GL_LIGHT5);
		l->setNumberGlLight(GL_LIGHT5);
		break;
	case (6):
		glEnable(GL_LIGHT6);
		l->setNumberGlLight(GL_LIGHT6);
		break;
	case (7):
		glEnable(GL_LIGHT7);
		l->setNumberGlLight(GL_LIGHT7);
		break;
	//default :
		//l = nullptr;
			//throw exception
	}

//	int i = 0x4007;
	//scene_lights[number_scene_lights] = *l;
	scene_lights.push_back(l);
	number_scene_lights ++;
	
	return l;
}

std::list <Light*> SceneManager::getSceneLights(){

	return scene_lights;

}

int SceneManager::getLightsNumber(){

	return number_scene_lights;
}

void SceneManager::destroyCamera(const std::string  & stringName){

	Camera * destroyCam;

	for (std::list<Camera*>::iterator it = camera_list.begin(); it != camera_list.end(); ++it) 
	{
		if((*it)->getName() == stringName)
		{
			destroyCam = (*it);
		}
	}
	cout << "length before destroy" << camera_list.size() << endl;
	camera_list.remove(destroyCam);
	cout << "length after destroy" << camera_list.size() << endl;
}

void SceneManager::renderScene(){

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	std::list<Camera*>::iterator cam_it;
	std::list<Light*>::iterator light_it;

	for ( cam_it = camera_list.begin(); cam_it != camera_list.end(); ++cam_it){
	
		(**cam_it).updateCamera();

		for ( light_it = scene_lights.begin(); light_it != scene_lights.end(); ++light_it){
		
			(**light_it).updadeLight();
			
		}

		this->getRootTransformNode()->updateNode();

		
		
	}
	
	SDL_GL_SwapBuffers();

	
	
}




//deleteEngine

		/* clean ourselves up and exit */
		//Quit( 0 );
