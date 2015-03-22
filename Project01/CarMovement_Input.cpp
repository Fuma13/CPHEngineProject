#include "CarMovement_InputWord.h"

CarMovement_InputWord::CarMovement_InputWord(int count_gameStates) : InputWord(count_gameStates)
{
	x_velocity = 0;
	y_velocity = 0;
}

InputEvent* CarMovement_InputWord::update(SDL_Event _event)
{
	CarMovement_InputEvent* carMovementEvent = new CarMovement_InputEvent();
	event_current = _event;

	switch(_event.type)
	{
		case SDL_KEYDOWN:

			switch (_event.key.keysym.sym)
			{
				//north
				case SDLK_UP:
					y_velocity = -1;
					break;
				//east
				case SDLK_RIGHT:
					x_velocity = 1;
					break;
				//south
				case SDLK_DOWN:
					y_velocity = 1;
					break;
				//west
				case SDLK_LEFT:
					x_velocity = -1;
					break;
				default:
					break;
			}
			break;

		case SDL_KEYUP:
            switch(_event.key.keysym.sym)
			{
				case SDLK_UP:
					if( y_velocity < 0 )
					y_velocity = 0;
					break;
				case SDLK_RIGHT:
					if( x_velocity > 0 )
					x_velocity = 0;
					break;
				case SDLK_DOWN:
					if( y_velocity > 0 )
					y_velocity = 0;
                    break;
				case SDLK_LEFT:
					if( x_velocity < 0 )
					x_velocity = 0;
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

	carMovementEvent->set_x_velocity(x_velocity);
	carMovementEvent->set_y_velocity(y_velocity);
	carMovementEvent->set_eventHasOccured(true);

	 return carMovementEvent;
}



