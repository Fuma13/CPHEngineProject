#include "GamePlay_02.h"
#include "GameObject.h"
#include "Root.h"
//#include "SceneManager.h"
#define newCamera(x) SceneManager::getInstance()->createCamera(x)

GamePlay_02 * GamePlay_02::m_instance = NULL;

GamePlay_02 * GamePlay_02::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new (EAllocationType::GAMEOBJECTS)  GamePlay_02();
	}
	return m_instance;
}

GamePlay_02::GamePlay_02()
{
	name = "GamePlay_02";
	//newAgeCube = new CubeObjectTest("d", Vector3 (0.0,0.0,0.0), Quaternion.IDENTITY);
}

void GamePlay_02::init() 
{
	
	
	cube_01 = new (EAllocationType::GAMEOBJECTS) CubeObjectTest("node_2");
	
	cam = newCamera("camera2");//SceneManager::getInstance()->createCamera("camera1");
	light2 = *SceneManager::getInstance()->getSceneLights().begin();
	light2->setType(Light::LightTypes::LT_POINT);
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
	mat05 = new Material("mat05");

	Root * mRoot = Root::getInstance(); 
	
	cube_01->init(1);
	//cube_02->init(3);
	cam->setPosition(Vector3(0.0f,0.0f,-15.0f));
	
	cube_01->mMesh->setMaterial(mat05);
	mat05->setDiffiuseColour(0.0,1.0,0.0);

	//mat_01->setTexture2D(tex2d);



}
//GamePlay_02::~GamePlay_02()
//{
//	SceneManager::getInstance()->destroyCamera("camera2");
//	delete cube_01;
//}
void GamePlay_02::destroy()
{
	SceneManager::getInstance()->destroyCamera("camera2");
	cube_01->~CubeObjectTest();
	MemoryManagement::operator delete(cube_01,EAllocationType::NO_ASSIGNED);
}

bool GamePlay_02::update(vector<Event*> events)
{
	Matrix3 * mt3 = new Matrix3;
	*mt3 = cam->getLocalAxes();
	
	for (vector<Event*>::iterator it = events.begin(); it != events.end(); ++it) 
	{
		
		//check whether its a CMIE
		if(CameraMovementInputEvent * cME = dynamic_cast<CameraMovementInputEvent *>(*it)) 
		{
			Vector2 position = cME->get_current_position();
			currentFramePositionx = position.x;
			currentFramePositiony = position.y;
			//cout << position.x << " . " << position.y << endl;
		}
		if(FourDirectionsMovement_InputEvent * fDM = dynamic_cast<FourDirectionsMovement_InputEvent *>(*it)) 
		{
			x_vel = fDM->get_x_velocity();
			y_vel = fDM->get_y_velocity();
		}
		if(CarMovement_InputEvent * cM = dynamic_cast<CarMovement_InputEvent *>(*it))
		{
			x_vel_li = cM->get_x_velocity();
			y_vel_li = cM->get_y_velocity();
			
			if(x_vel_li != 0){
			light2->setPosition(Vector3(0.0,light2->getPosition().y,light2->getPosition().z+(0.3* x_vel_li)));
			
			}
			if(y_vel_li != 0  ){
				
			light2->setPosition(Vector3(0.0,light2->getPosition().y+(0.3* -y_vel_li),light2->getPosition().z));
			}
			
		}
	}


	if (x_vel != 0)
	{
	
		cam->translate( Vector3(-1.0,0.0,0.0)*(x_vel * speed),MovableObject::TransformSpace::TS_WORLD);
		
	}

	if (y_vel != 0)
	{

		cam->translate(Vector3(0.0,0.0,-1.0)*(y_vel * speed),MovableObject::TransformSpace::TS_WORLD);
	}


	xrot_zero = (currentFramePositionx -512) - (lastFramePositionx);
	yrot_zero = (currentFramePositiony -384) - (lastFramePositiony);
	lastFramePositionx = currentFramePositionx -512;
	lastFramePositiony = currentFramePositiony -384;
	xrot += xrot_zero;
	yrot += yrot_zero;
	
	
	Quaternion qtr1;Quaternion qtr2;Quaternion qtr3;
	qtr1 = Quaternion(Radian(xrot_zero /100),Vector3(0.0,1.0,0.0));
	qtr2 = Quaternion(Radian(yrot_zero /100),Vector3(1.0,0.0,0.0));
	qtr3 = (qtr1 * qtr2);
	qtr3.normalise();
	cam->rotate(qtr3,MovableObject::TransformSpace::TS_PARENT);
	
	

	return true;
}

string GamePlay_02::get_name(){return name;}
