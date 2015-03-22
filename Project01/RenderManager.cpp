#define NO_SDL_GLEXT
#include <GL\glew.h>
#include "RenderManager.h"


RenderManager * RenderManager::m_instance = NULL;

RenderManager * RenderManager::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new RenderManager();
	}
	return m_instance;
}

RenderManager::RenderManager()
{
	
}

void RenderManager::Quit( int returnCode )
{
	//clean up the window 
	SDL_Quit();
	// and exit appropriately 
	exit( returnCode );
}

int RenderManager::initializeRender()
{

	try
	{
		
		SDL_Surface *surface;
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
		/* Enable smooth shading */
		glShadeModel( GL_SMOOTH );

		/* Set the background Color*/
		glClearColor( .0f, .0f, .0f, 0.0f );

		/* Depth buffer setup */
		glClearDepth( 17.0f );

		/* Enables Depth Testing */
		glEnable( GL_DEPTH_TEST );

		/* Enables Light */
		glEnable( GL_LIGHTING);
		

		/*Enable gouraud shading */
		glShadeModel(GL_SMOOTH);	

		/* The Type Of Depth Test To Do */
		glDepthFunc( GL_LEQUAL );

		/* Really Nice Perspective Calculations */
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

		GLfloat ratio;

		/* Protect against a divide by zero */
		

		ratio = SCREEN_WIDTH/SCREEN_HEIGHT;
		/* Setup our viewport. */
		glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );

		/* change to the projection matrix and set our viewing volume. */
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity( );

		/* Set our perspective */
		gluPerspective( 45.0f, ratio, 0.1f, 10000.0f );

		/* Make sure we're chaning the model view and not the projection */
		glMatrixMode( GL_MODELVIEW );

		/* Reset The View */
		glLoadIdentity( );

		glewInit();
		if(glewIsSupported("GL_VERSION_3_2"))
			cout << "Ready for OpenGL 3.2 \n" << endl;
		else
		{
			cout << "OpenGL 3.2 not supported \n" << endl;
			//exit(1);
		}

		/* Should never get here */
		return( 0 );
	}
		catch(char e)
		{		
			std::cout << "error  " << e << std::endl; 
		}

}