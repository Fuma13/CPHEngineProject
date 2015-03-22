#ifndef A_H
#define A_H
#pragma once
/*
 * This is template created for Game Engines 2011 based on the SDL examples from http://nehe.gamedev.net/
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include "TransformNode.h"
#include <string>
#include "Mesh.h"
#include "RootTransformNode.h"
#include "SceneManager.h"
#include <gl\gl.h>                         // Header File For The OpenGL32 Library
#include <gl\glu.h>                            // Header File For The GLu32 Library
#include <Windows.h>
#include <wchar.h>
#include "Vector4.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Vector2.h"
#include "InputManager.h"
#include <typeinfo.h>

/* screen width, height, and bit depth */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP     16

/* Define our booleans */
#define TRUE  1
#define FALSE 0






using namespace std;

class A
{

private:
	TransformNode * node1 ;
	TransformNode * node4 ;
	TransformNode * node2 ;
	TransformNode * node3 ;
	TransformNode * node5 ;
    SceneManager * sc_mng;
	float translate_ratio;
	GLfloat stam_arr[16];
	Mesh * cube ;
	Mesh * cube2;
	Camera * cam;
	SDL_Event keyevent;
	Vector2 pos;
	int posx, posy;

	bool rotateFlagUP;
	bool rotateFlagDOWN;
	bool rotateFlag;
	GLfloat angle;

	/*light*/

	float lightAmbient[4];
	float lightDiffuse[4];
	float lightPosition[4];
	float matAmbient[4];
	float matDiffuse[4];

	//Input
	InputManager inputManager_instance;
	list<Event*> event_list;




	/* This is our SDL surface */
	SDL_Surface *surface;
public:

	A(){}
	A(SDL_Surface *passed_surface)
	{
		surface=passed_surface;

		translate_ratio = 0.0;
		stam_arr[16];
		pos = Vector2(0.0,0.0);
		rotateFlagUP = FALSE;
		rotateFlagDOWN = FALSE;
		rotateFlag = FALSE;
		angle = 0.05f;

	/*light*/

		lightAmbient[0] = 1.0f;
		lightAmbient[1] = 1.0f;
		lightAmbient[2] = 1.0;
		lightAmbient[3] = 1.0f;
		lightDiffuse[0] = 1.0f;
		lightDiffuse[1] = 1.0f;
		lightDiffuse[2] = 1.0f;
		lightDiffuse[3] = 1.0f;
		lightPosition[0] = 0.0f;
		lightPosition[1] = 0.0f;
		lightPosition[2] = 2.0f;
		lightPosition[3] = 1.0f ;
		matAmbient[0] = 0.3f;
		matAmbient[1] = 0.0f;
		matAmbient[2] = 0.0f;
		matAmbient[3] = 1.0f;
		matDiffuse[0] = 0.6f;
		matDiffuse[1] = 0.6f;
		matDiffuse[2] = 0.6f;
		matDiffuse[3] = 1.0f;
	}
/* function to release/destroy our resources and restoring the old desktop */
void Quit( int returnCode )
{
	/* clean up the window */
	SDL_Quit( );

	/* and exit appropriately */
	exit( returnCode );
}


/* function to reset our viewport after a window resize */
int resizeWindow( int width, int height )
{
	/* Height / width ration */
	GLfloat ratio;

	/* Protect against a divide by zero */
	if ( height == 0 )
	height = 1;

	ratio = ( GLfloat )width / ( GLfloat )height;

	/* Setup our viewport. */
	glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

	/* change to the projection matrix and set our viewing volume. */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	/* Set our perspective */
	gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

	/* Make sure we're chaning the model view and not the projection */
	glMatrixMode( GL_MODELVIEW );

	/* Reset The View */
	glLoadIdentity( );
	return( TRUE );
}


/* general OpenGL initialization function */
int initGL( GLvoid )
{
	/* Enable smooth shading */
	glShadeModel( GL_SMOOTH );

	/* Set the background Color*/
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	/* Depth buffer setup */
	glClearDepth( 17.0f );

	/* Enables Depth Testing */
	glEnable( GL_DEPTH_TEST );

	/* Enables Light */
	glEnable( GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	/*Enable gouraud shading */
	glShadeModel(GL_SMOOTH);	

	/* The Type Of Depth Test To Do */
	glDepthFunc( GL_LEQUAL );

	/* Really Nice Perspective Calculations */
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	return( TRUE );
}

void initScenegraph() 
{
	// TODO: Why initialise SceneManager in the OpenGL init?
	sc_mng = SceneManager::getInstance();

	//node1 = new RootTransformNode ("node1",0.0,0.0,0.0);
	
	cam = sc_mng->createCamera("camera1");
	node1 = sc_mng->getRootTransformNode()->createChild("node1"); 
	node2 = node1->createChild("node2");
	node3 = node2->createChild ("node3",Vector3(0.2f,0.0f,0.0f));
	node4 = node3->createChild("node4");
	node5 = sc_mng->getRootTransformNode()->createChild("node5"); 
	//node1->getOrientation();

	cube = new Mesh(0.4,1.0,0.0,0.0);
	cube2 = new Mesh(0.3,0.0,0.0,1.0);
	Mesh * cube3 = new Mesh(0.2,0.0,1.0,0.0);
	Mesh * cube4 = new Mesh(0.3,0.5,0.0,0.5);

	node2->attachObject(cube);
	node3->attachObject(cube2);
	node4->attachObject(cube3);
	node5->attachObject(cube4);
	node2->setOrientation(Quaternion(12,0.0,0.0,1.0));
	//node2->setOrientation(Quaternion(5,0.0,1.0,0.0));

	//sc_mng->startEngine(true,60,10);

}

/* function to handle key press events */
void handleKeyPress( SDL_keysym *keysym)
{
	switch ( keysym->sym )
	{
	case SDLK_ESCAPE:
		/* ESC key was pressed */
		Quit( 0 );
		break;
	case SDLK_F1:
		/* F1 key was pressed
		 * this toggles fullscreen mode
		 */
		SDL_WM_ToggleFullScreen( surface );
		break;
	case SDLK_DOWN:
		/* down  Rotation Mesh_02*/
		rotateFlagDOWN = TRUE;
		break;
	case SDLK_UP:
		/* up  Rotation Mesh_02*/
		rotateFlagUP = TRUE;
		break;
	case SDLK_RIGHT:
		/*start rotation*/
		rotateFlag=TRUE;
		break;
	case SDLK_LEFT:
		/*stop rotation*/
		rotateFlag=FALSE;
		break;
	default:
		break;
	}

	return;
}





/* Here goes our drawing code */
int drawGLScene( GLvoid )
{
	 
	
	/*
	if ( translate_ratio > 5){

		//node3->changeParent(node1,0.0,0.0,0.0);

		//node3->changeParent(node1);
	}
	*/


	/* Clear The Screen And The Depth Buffer */
	
	 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//glLoadIdentity();
	//glRotatef(180,0.0,1.0,0.0);
	//glTranslatef(0.0,0.0,-3.0);
	//gluLookAt(0.0,1.0,3.0,0.0,0.0,0.0,0.0,1.0,0.0);
	//cam->setPosition(Vector3(0.0,0.0,-3.0));

	
	 /*
	
	glPushMatrix();
	glBegin(GL_LINES);

	glColor3f(1.0,0.0,0.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(0.0f, 100000.0f, 0.0f); // ending point of the line

	glColor3f(0.0,1.0,0.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(0.0f, 0.0f, 100000.0f); // ending point of the line

	glColor3f(0.0,0.0,1.0);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(100000.0f, 0.0f, 0.0f); // ending point of the line

	glEnd();
	glPopMatrix();
	*/
	
	
	if(keyevent.type == SDL_KEYDOWN){
	
		if(keyevent.key.keysym.sym == SDLK_w){

			cam->translate(Vector3(0.0,0.0,0.002),MovableObject::TS_LOCAL);
	
		}
	
		if(keyevent.key.keysym.sym == SDLK_s){

			cam->translate(Vector3(0.0,0.0,-0.002),MovableObject::TS_LOCAL);
			cout << "Michele want to be nacked" << endl;
		}

				if(keyevent.key.keysym.sym == SDLK_d){

			cam->translate(Vector3(-0.002,0.0,0.0),MovableObject::TS_LOCAL);
			
	
		}
	
		if(keyevent.key.keysym.sym == SDLK_a){

			cam->translate(Vector3(0.002,0.0,0.0),MovableObject::TS_LOCAL);
		}

		if(keyevent.key.keysym.sym == SDLK_z){

			cam->rotate(Quaternion(0.0002,0.0,1.0,0.0),MovableObject::TS_PARENT);
	
		}
	
		if(keyevent.key.keysym.sym == SDLK_x){

			cam->rotate(Quaternion(-0.0002,0.0,1.0,0.0),MovableObject::TS_PARENT);
		}

		if(keyevent.key.keysym.sym == SDLK_c){

			cam->rotate(Quaternion(0.0002,1.0,0.0,0.0),MovableObject::TS_PARENT);
	
		}
	
		if(keyevent.key.keysym.sym == SDLK_v){

			cam->rotate(Quaternion(-0.0002,1.0,0.0,0.0),MovableObject::TS_PARENT);
		}
	}



	

	//node3->translate (Vector3 (0.5,0.0,-1.0));
	//node2->rotate(translate_ratio);
	//node2->scale(Vector3(0.08,0.08,0.08));
	node3->setPosition(Vector3(1.2,0.0,0.0));
	node4->setPosition(Vector3(0.8,0.0,0.0));
	//node2->translate(Vector3(0.002,0.0,0.0),TransformNode::TransformSpace::TS_WORLD);
	//node2->stampMatrix();
	node2->rotate(Quaternion(9000,0.0,1.0,0.0),MovableObject::TS_PARENT);
	//node2->rotate(Vector3(1.0,0.5,1.0),Radian(0.0001),MovableObject::TS_PARENT);
	node3->rotate(Quaternion(8000,0.0,1.0,0.0),MovableObject::TS_PARENT);
	node5->setPosition(Vector3(1.2,0.0,0.0));
	node5->setOrientation(Quaternion(node4->getOrientation()));
	//node2->setOrientation(Quaternion(90.0,0.0,1.0,0.0));
	
	
	sc_mng->renderScene();
	
	//node1->stampMatrix();
	
	
	/*HERE you should put your code in order to do render something on the screen, use lighting, modify the camera position etc... */

	//TODO: why does it return 666 in the first run
	//GLfloat pass[3] = {mesh_01->get_translation(0)+movecam, mesh_01->get_translation(1), mesh_01->get_translation(2)};

	
	
	
	/* Draw it to the screen */
	SDL_GL_SwapBuffers( );


	return( TRUE );
}



int amain()
{
	//triangle_tester();

	try
	{
		

		/* Flags to pass to SDL_SetVideoMode */
		int videoFlags;
		/* main loop variable */
		int done = FALSE;
		/* used to collect events */
		SDL_Event event;
		/* this holds some info about our display */
		const SDL_VideoInfo *videoInfo;



		/* initialize SDL */
		if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			fprintf( stderr, "Video initialization failed: %s\n",
				 SDL_GetError( ) );
			Quit( 1 );
		}

		/* Fetch the video info */
		videoInfo = SDL_GetVideoInfo( );

		if ( !videoInfo )
		{
			fprintf( stderr, "Video query failed: %s\n",
				 SDL_GetError( ) );
			Quit( 1 );
		}

		/* the flags to pass to SDL_SetVideoMode */
		videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
		videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
		videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
		videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

		/* This checks to see if surfaces can be stored in memory */
		if ( videoInfo->hw_available )
			videoFlags |= SDL_HWSURFACE;
		else
			videoFlags |= SDL_SWSURFACE;

		/* This checks if hardware blits can be done */
		if ( videoInfo->blit_hw )
			videoFlags |= SDL_HWACCEL;

		/* Sets up OpenGL double buffering */
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

		/* get a SDL surface */
		surface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
					videoFlags );

		/* Verify there is a surface */
		if ( !surface )
		{
			fprintf( stderr,  "Video mode set failed: %s\n", SDL_GetError( ) );
			Quit( 1 );
		}

		/* initialize OpenGL */
		initGL( );


		initScenegraph();

		/* resize the initial window */
		resizeWindow( SCREEN_WIDTH, SCREEN_HEIGHT );

		/* wait for events */ 
		while ( !done )
		{
			inputManager_instance.handle_input();
			event_list.clear();

			if(inputManager_instance.get_input_events().empty() == false)
			{
				vector<Event*> temp_vector = inputManager_instance.get_input_events();
				for (vector<Event*>::iterator it = temp_vector.begin(); it != temp_vector.end(); ++it) 
				{
					event_list.push_front(*it);
				}
			}

			/* handle the events in the queue */

			while ( SDL_PollEvent( &keyevent ) )
			{
				switch( keyevent.type )
				{
			  
				case SDL_VIDEORESIZE:
					/* handle resize event */
					surface = SDL_SetVideoMode( keyevent.resize.w,
							keyevent.resize.h,
							16, videoFlags );
					if ( !surface )
					{
						fprintf( stderr, "Could not get a surface after resize: %s\n", SDL_GetError( ) );
						Quit( 1 );
					}
					resizeWindow( keyevent.resize.w, keyevent.resize.h );
					break;
				case SDL_KEYDOWN:
					/* handle key presses */
					handleKeyPress( &keyevent.key.keysym);
					cout << "bla bla bla" << endl;
					break;
				case SDL_QUIT:
					/* handle quit requests */
					done = TRUE;
					break;
				default:
					break;


				}
			}
		
			for (list<Event*>::iterator it = event_list.begin(); it!=event_list.end(); ++it) 
			{
				if(CameraMovementInputEvent * cME = dynamic_cast<CameraMovementInputEvent *>(*it)) 
				{
					Vector2 position = cME->get_current_position();
					cout << position.x << " . " << position.y << endl;
				}
			}

			/* draw the scene */
			drawGLScene( );
		}

		if (done){
	
			delete sc_mng;
	
		}

		/* clean ourselves up and exit */
		Quit( 0 );

		/* Should never get here */
		return( 0 );
	}
		catch(char e)
		{		
			std::cout << "error  " << e << std::endl; 
		}
	}

	
};

#endif

