#include "EngineControls_InputWord.h"


EngineControls_InputWord::EngineControls_InputWord(int count_gameStates) : InputWord(count_gameStates)
{
	gotoGameState = -1;
	keypress_combination01_key01 = false;
	keypress_combination01_key02 = false;
	keypress_combination01_key03 = false;
	keypress_combination01_key04 = false;
	keypress_combination01_key05 = false;
}

InputEvent* EngineControls_InputWord::update(SDL_Event _event)
{
	EngineControls_InputEvent* engineControlsEvent = new EngineControls_InputEvent();
	event_current = _event;

	switch(_event.type)
	{
		case SDL_KEYDOWN:

			switch (_event.key.keysym.sym)
			{
				case SDLK_k:
					keypress_combination01_key01 = true;
					break;
				case SDLK_1:
					keypress_combination01_key02 = true;
					break;
				case SDLK_2:
					keypress_combination01_key03 = true;
					break;
				case SDLK_3:
					keypress_combination01_key04 = true;
					break;
				case SDLK_4:
					keypress_combination01_key05 = true;
					break;
				default:
					break;
			}
			break;

        case SDL_KEYUP:
            switch(_event.key.keysym.sym)
			{
				case SDLK_k:
					keypress_combination01_key01 = false;
					break;
				case SDLK_1:
					keypress_combination01_key02 = false;
					break;
				case SDLK_2:
					keypress_combination01_key03 = false;
					break;
				case SDLK_3:
					keypress_combination01_key04 = false;
					break;
				case SDLK_4:
					keypress_combination01_key05 = false;
					break;
				default:
					break;
            }
			break;
		 
		default:
			// TODO warn that an event that is not useful has been sent, and this should not happen!!!
			cout << "WARNING: An InputWord has received an input event that is not handled in the switch/case" << endl;

			break;
	}

	if (keypress_combination01_key01)
	{
		if(keypress_combination01_key02) 
		{
			gameState = (EGameState)0;		
			engineControlsEvent->set_gamestateRequest(gameState);
			engineControlsEvent->set_eventHasOccured(true);
		}
		if(keypress_combination01_key03) 
		{
			gameState = (EGameState)1;
			engineControlsEvent->set_gamestateRequest(gameState);
			engineControlsEvent->set_eventHasOccured(true);
		}
		if(keypress_combination01_key04)
		{
			gameState = (EGameState)2;
			engineControlsEvent->set_gamestateRequest(gameState);
			engineControlsEvent->set_eventHasOccured(true);
		}
		if(keypress_combination01_key05)
		{
			gameState = (EGameState)3;
			engineControlsEvent->set_gamestateRequest(gameState);
			engineControlsEvent->set_eventHasOccured(true);
		}
	}
		return engineControlsEvent;
}