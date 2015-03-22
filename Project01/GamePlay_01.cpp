#include "GamePlay_01.h"
#include "GameObject.h"
#include "Root.h"
//#include "Light.h"
//#include "Material.h"
//#include "SceneManager.h"
#define newCamera(x) SceneManager::getInstance()->createCamera(x)

GamePlay_01 * GamePlay_01::m_instance = NULL;


GamePlay_01 * GamePlay_01::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new (EAllocationType::GAMEOBJECTS) GamePlay_01();
	}
	return m_instance;
}

GamePlay_01::GamePlay_01()
{
	
	name = "GamePlay_01";
	
	
	
	//newAgeCube = new CubeObjectTest("d", Vector3 (0.0,0.0,0.0), Quaternion.IDENTITY);
}

void GamePlay_01::init() 
{
	
	mat_manager = MaterialManager::getInstance();
	mat_manager->enableDefaultMaterial();
	cube_01 = new (EAllocationType::GAMEOBJECTS) CubeObjectTest("node_1");
	light1 = SceneManager::getInstance()->createLight("light01",Light::LightTypes::LT_SPOTLIGHT);
	light1->setPosition(Vector3(0.0,0.0,8.0));
	light1->setDirection(Vector3(0.0,0.0,-1.0));
	light1->setType(Light::LightTypes::LT_SPOTLIGHT);
	//light1->setDiffuseColour(0.8,0.8,0.8);
	//light2 = SceneManager::getInstance()->createLight("light02",Light::LightTypes::LT_SPOTLIGHT);
	//light2->setPosition(Vector3(0.0,0.0,8.0));
	//light2->setDirection(Vector3(0.0,0.0,-1.0));
	//light2->setDiffuseColour(0.8,0.0,0.0);
	mat_01 = new Material ("mat_01");
	tex2d = ResourceManager::getInstance()->loadTexture("texture.raw",256,256);
	
	
	//newAgeCube = new CubeObjectTest("d", Vector3 (0.0,0.0,0.0), Quaternion.IDENTITY);


	//SceneManager * sc_mn = SceneManager::getInstance();
	cam = newCamera("camera1");//SceneManager::getInstance()->createCamera("camera1");

	
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


	Root * mRoot = Root::getInstance(); 
	
	cube_01->init(1);
	//cube_02->init(3);
	cam->setPosition(Vector3(0.0f,0.0f,-15.0f));
	
	cube_01->mMesh->setMaterial(mat_01);

	mat_01->setDiffiuseColour(0.7,0.0,0.0);
	mat_01->setShineValue(110);
	//mat_01->setTexture2D(tex2d);

	
}



void GamePlay_01::destroy()
{
	SceneManager::getInstance()->destroyCamera("camera1");
	cube_01->~CubeObjectTest();
	MemoryManagement::operator delete(cube_01,EAllocationType::NO_ASSIGNED);
}

bool GamePlay_01::update(vector<Event*> events)
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
			light1->setPosition(Vector3(0.0,light1->getPosition().y,light1->getPosition().z+(0.3* x_vel_li)));
			
			}
			if(y_vel_li != 0  ){
				
			light1->setPosition(Vector3(0.0,light1->getPosition().y+(0.3* -y_vel_li),light1->getPosition().z));
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

string GamePlay_01::get_name(){return name;}
