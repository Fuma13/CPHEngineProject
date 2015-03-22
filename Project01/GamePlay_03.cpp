#include "GamePlay_03.h"
#include "GameObject.h"
#include "Root.h"
#define newCamera(x) SceneManager::getInstance()->createCamera(x)

GamePlay_03 * GamePlay_03::m_instance = NULL;

GamePlay_03 * GamePlay_03::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new (EAllocationType::GAMEOBJECTS)  GamePlay_03();
	}
	return m_instance;
}

GamePlay_03::GamePlay_03()
{
	name = "GamePlay_03";
	//newAgeCube = new CubeObjectTest("d", Vector3 (0.0,0.0,0.0), Quaternion.IDENTITY);
}

void GamePlay_03::init() 
{
	light3 = *SceneManager::getInstance()->getSceneLights().begin();
	light3->setType(Light::LightTypes::LT_DIRECTIONAL);
	light3->setDirection(Vector3(0.0,1.0,0.0));
	cam = newCamera("camera3");//SceneManager::getInstance()->createCamera("camera1");

	x_vel = 0;
	y_vel = 0;
	speed = 1;
	xrot = 1;
	yrot = 1;
	xrot_zero = 0;
	currentFramePositionx = 0;
	lastFramePositionx = 0;
	yrot_zero = 0;
	currentFramePositiony = 0;
	lastFramePositiony = 0;
	cam->setPosition(Vector3(0.0f,0.0f,-15.0f));

	Root * mRoot = Root::getInstance(); 

	playerCar = new (EAllocationType::GAMEOBJECTS)  PlayerCar("pCar_01");
	playerCar ->init();

	car = new (EAllocationType::AI)  AICar("cCar_01");
	car ->init(1);
	mat_02 = new Material("mat_02");
	mat_03 = new Material("mat_03");
	/*car2 = new AICar("cCar_02");
	car2 ->init(2);*/

	car->mTransformNode->setPosition(Vector3(20.0,0.0,0.0));
	car->mMesh->setMaterial(mat_02);
	mat_02->setDiffiuseColour(0.0,1.0,0.0);
	playerCar->mMesh->setMaterial(mat_03);
	mat_03->setDiffiuseColour(1.0,0.0,0.0);
}
//GamePlay_03::~GamePlay_03()
//{
//	SceneManager::getInstance()->destroyCamera("camera2");
//	delete playerCar;
//}

void GamePlay_03::destroy()
{
	SceneManager::getInstance()->destroyCamera("camera3");
	playerCar->~PlayerCar();
	car->~AICar();
	MemoryManagement::operator delete(playerCar,(EAllocationType::NO_ASSIGNED)) ;
	MemoryManagement::operator delete(car,(EAllocationType::NO_ASSIGNED)) ;
}

bool GamePlay_03::update(vector<Event*> events)
{
	Matrix3 * mt3 = new Matrix3;
	*mt3 = cam->getLocalAxes();
	car->mMesh->getMaterial()->setDiffiuseColour(0.0,0.0,1.0);
	for (vector<Event*>::iterator it = events.begin(); it != events.end(); ++it) 
	{
		if(CameraMovementInputEvent * cME = dynamic_cast<CameraMovementInputEvent *>(*it)) 
		{
			Vector2 position = cME->get_current_position();
			currentFramePositionx = position.x;
			currentFramePositiony = position.y;
		}
		if(FourDirectionsMovement_InputEvent * fDM = dynamic_cast<FourDirectionsMovement_InputEvent *>(*it)) 
		{
			x_vel = fDM->get_x_velocity();
			y_vel = fDM->get_y_velocity();
		}

		//Here we demonstrate selecting events in the code for the level.
		//This is just an option in case the programmer wants to write some part of his
		//game logic inside the code for the game state instead of writing it inside
		//game objects.
		if(CarMovement_InputEvent * cM = dynamic_cast<CarMovement_InputEvent *>(*it))
		{
			playerCar->handleInput(cM);
		}
	}

	if (x_vel != 0)
	{
		cam->translate((mt3->getColumn(0) * x_vel * speed),MovableObject::TransformSpace::TS_WORLD);
	}

	if (y_vel != 0)
	{
		cam->translate((mt3->getColumn(2) * y_vel * speed),MovableObject::TransformSpace::TS_WORLD);
	}

	car->onAI();
	playerCar->update();

	return true;
}

string GamePlay_03::get_name(){return name;}
