// good article: http://www.gamedev.net/blog/355/entry-2250186-designing-a-robust-input-handling-system-for-games/
// maybe interesting: http://dominikgrabiec.com/category/gamedev/
// sdl documentation: http://www.libsdl.org/docs/html/eventstructures.html

/*
    Returns:    Input_Manager::SIGNAL enumeration:
                    NORMAL - on normal loop returns
                    QUIT   - on request for program termination
*/
#ifndef InputManager_H
#define InputManager_H

#pragma once

#include <vector>
#include "InputWord.h"

#include "CameraMovementInputWord.h"
#include "FourDirectionsMovement_InputWord.h"
#include "EngineControls_InputWord.h"
#include "CarMovement_InputWord.h"

using namespace std;

class InputManager
{
public:
    /*  Here we define the signals we need to let our parent know the status
        of the program. */
    enum SIGNAL
	{
        NORMAL,     //handle_input() processed input correctly
        QUIT        //handle_input() says the user wants to exit the program
    };

	static InputManager * getInstance();

/*  General function called to interpret all user input. 
    Returns Input_Manager::NORMAL on normal loop returns
            Input_Manager::QUIT when user requests to quit.  */
    SIGNAL handle_input();
    
	/*Returns the events that have happend since handle_input() was called last time*/
	vector<Event*> get_input_events()
		{	
			return input_events;
		}

protected:

	InputManager();

	InputEvent* inputEvent;
	//bool mouse_button_currently_pressed;
	vector<InputWord*> input_words;
	vector<Event*> input_events;

private:

	static InputManager * m_instance;
	~InputManager();

    /*  SDL Event that contains the input device data from the last query  */
    SDL_Event _event;
    
};
#endif




///////* function to reset our viewport after a window resize */
//////int resizeWindow( int width, int height )
//////{
//////	/* Height / width ration */
//////	GLfloat ratio;
//////
//////	/* Protect against a divide by zero */
//////	if ( height == 0 )
//////	height = 1;
//////
//////	ratio = ( GLfloat )width / ( GLfloat )height;
//////
//////	/* Setup our viewport. */
//////	glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
//////
//////	/* change to the projection matrix and set our viewing volume. */
//////	glMatrixMode( GL_PROJECTION );
//////	glLoadIdentity( );
//////
//////	/* Set our perspective */
//////	gluPerspective( 45.0f, ratio, 0.1f, 100.0f );
//////
//////	/* Make sure we're chaning the model view and not the projection */
//////	glMatrixMode( GL_MODELVIEW );
//////
//////	/* Reset The View */
//////	glLoadIdentity( );
//////	return( TRUE );
//////}
//////
//////
///////* Here goes our drawing code */
//////int drawGLScene( GLvoid )
//////{
//////	 
//////	
//////	/*
//////	if ( translate_ratio > 5){
//////
//////		node3->changeParent(node1,0.0,0.0,0.0);
//////
//////		node3->changeParent(node1);
//////	}
//////	*/
//////
//////
//////	/* Clear The Screen And The Depth Buffer */
//////	
//////	 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//////
//////	glLoadIdentity();
//////	glRotatef(180,0.0,1.0,0.0);
//////	glTranslatef(0.0,0.0,-3.0);
//////	gluLookAt(0.0,1.0,3.0,0.0,0.0,0.0,0.0,1.0,0.0);
//////	cam->setPosition(Vector3(0.0,0.0,-3.0));
//////
//////	
//////	 /*
//////	
//////	glPushMatrix();
//////	glBegin(GL_LINES);
//////
//////	glColor3f(1.0,0.0,0.0);
//////	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
//////	glVertex3f(0.0f, 100000.0f, 0.0f); // ending point of the line
//////
//////	glColor3f(0.0,1.0,0.0);
//////	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
//////	glVertex3f(0.0f, 0.0f, 100000.0f); // ending point of the line
//////
//////	glColor3f(0.0,0.0,1.0);
//////	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
//////	glVertex3f(100000.0f, 0.0f, 0.0f); // ending point of the line
//////
//////	glEnd();
//////	glPopMatrix();
//////	*/
//////	
//////	
//////	if(keyevent.type == SDL_KEYDOWN){
//////	
//////		if(keyevent.key.keysym.sym == SDLK_w){
//////
//////			cam->translate(Vector3(0.0,0.0,0.002),MovableObject::TS_LOCAL);
//////	
//////		}
//////	
//////		if(keyevent.key.keysym.sym == SDLK_s){
//////
//////			cam->translate(Vector3(0.0,0.0,-0.002),MovableObject::TS_LOCAL);
//////		}
//////
//////				if(keyevent.key.keysym.sym == SDLK_d){
//////
//////			cam->translate(Vector3(-0.002,0.0,0.0),MovableObject::TS_LOCAL);
//////	
//////		}
//////	
//////		if(keyevent.key.keysym.sym == SDLK_a){
//////
//////			cam->translate(Vector3(0.002,0.0,0.0),MovableObject::TS_LOCAL);
//////		}
//////
//////		if(keyevent.key.keysym.sym == SDLK_z){
//////
//////			cam->rotate(Quaternion(0.0002,0.0,1.0,0.0),MovableObject::TS_PARENT);
//////	
//////		}
//////	
//////		if(keyevent.key.keysym.sym == SDLK_x){
//////
//////			cam->rotate(Quaternion(-0.0002,0.0,1.0,0.0),MovableObject::TS_PARENT);
//////		}
//////
//////		if(keyevent.key.keysym.sym == SDLK_c){
//////
//////			cam->rotate(Quaternion(0.0002,1.0,0.0,0.0),MovableObject::TS_PARENT);
//////	
//////		}
//////	
//////		if(keyevent.key.keysym.sym == SDLK_v){
//////
//////			cam->rotate(Quaternion(-0.0002,1.0,0.0,0.0),MovableObject::TS_PARENT);
//////		}
//////	}
//////
//////
//////
//////	
//////
//////	node3->translate (Vector3 (0.5,0.0,-1.0));
//////	node2->rotate(translate_ratio);
//////	node2->scale(Vector3(0.08,0.08,0.08));
//////	node3->setPosition(Vector3(1.2,0.0,0.0));
//////	node4->setPosition(Vector3(0.8,0.0,0.0));
//////	node2->translate(Vector3(0.002,0.0,0.0),TransformNode::TransformSpace::TS_WORLD);
//////	node2->stampMatrix();
//////	node2->rotate(Quaternion(9000,0.0,1.0,0.0),MovableObject::TS_PARENT);
//////	node2->rotate(Vector3(1.0,0.5,1.0),Radian(0.0001),MovableObject::TS_PARENT);
//////	node3->rotate(Quaternion(8000,0.0,1.0,0.0),MovableObject::TS_PARENT);
//////	node5->setPosition(Vector3(1.2,0.0,0.0));
//////	node5->setOrientation(Quaternion(node4->getOrientation()));
//////	node2->setOrientation(Quaternion(90.0,0.0,1.0,0.0));
//////	
//////	
//////	sc_mng->renderScene();
//////	
//////	node1->stampMatrix();
//////	
//////	
//////	/*HERE you should put your code in order to do render something on the screen, use lighting, modify the camera position etc... */
//////
//////	TODO: why does it return 666 in the first run
//////	GLfloat pass[3] = {mesh_01->get_translation(0)+movecam, mesh_01->get_translation(1), mesh_01->get_translation(2)};
//////
//////	
//////	
//////	
//////	/* Draw it to the screen */
//////	SDL_GL_SwapBuffers( );
//////
//////
//////	return( TRUE );
//////}
//////
//////
//////
///////* function to handle key press events */
//////void handleKeyPress( SDL_keysym *keysym )
//////{
//////	switch ( keysym->sym )
//////	{
//////	case SDLK_ESCAPE:
//////		/* ESC key was pressed */
//////		Quit( 0 );
//////		break;
//////	case SDLK_F1:
//////		/* F1 key was pressed
//////		 * this toggles fullscreen mode
//////		 */
//////		SDL_WM_ToggleFullScreen( surface );
//////		break;
//////	case SDLK_DOWN:
//////		/* down  Rotation Mesh_02*/
//////		rotateFlagDOWN = TRUE;
//////		break;
//////	case SDLK_UP:
//////		/* up  Rotation Mesh_02*/
//////		rotateFlagUP = TRUE;
//////		break;
//////	case SDLK_RIGHT:
//////		/*start rotation*/
//////		rotateFlag=TRUE;
//////		break;
//////	case SDLK_LEFT:
//////		/*stop rotation*/
//////		rotateFlag=FALSE;
//////		break;
//////	default:
//////		break;
//////	}
//////
//////	return;
//////}
//////
//////while ( SDL_PollEvent( &keyevent ) )
//////			{
//////				switch( keyevent.type )
//////				{
//////			  
//////				case SDL_VIDEORESIZE:
//////					/* handle resize event */
//////					surface = SDL_SetVideoMode( keyevent.resize.w,
//////							keyevent.resize.h,
//////							16, videoFlags );
//////					if ( !surface )
//////					{
//////						fprintf( stderr, "Could not get a surface after resize: %s\n", SDL_GetError( ) );
//////						Quit( 1 );
//////					}
//////					resizeWindow( keyevent.resize.w, keyevent.resize.h );
//////					break;
//////				case SDL_KEYDOWN:
//////					/* handle key presses */
//////					handleKeyPress( &keyevent.key.keysym );
//////					break;
//////				case SDL_QUIT:
//////					/* handle quit requests */
//////					done = TRUE;
//////					break;
//////				default:
//////					break;
//////
//////
//////				}
//////			}