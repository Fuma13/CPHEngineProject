#include "FourDirectionsMovement_InputWord.h"

FourDirectionsMovement_InputWord::FourDirectionsMovement_InputWord(int count_gameStates) : InputWord(count_gameStates)
{
	x_velocity = 0;
	y_velocity = 0;

}

InputEvent* FourDirectionsMovement_InputWord::update(SDL_Event _event)
{
	FourDirectionsMovement_InputEvent* fourDirectionalMovementEvent = new FourDirectionsMovement_InputEvent();
	event_current = _event;

	switch(_event.type)
	{
		case SDL_KEYDOWN:

			switch (_event.key.keysym.sym)
			{
				//north
				case SDLK_w:
					y_velocity = -1;
					break;
				//east
				case SDLK_d:
					x_velocity = 1;
					break;
				//south
				case SDLK_s:
					y_velocity = 1;
					break;
				//west
				case SDLK_a:
					x_velocity = -1;
					break;
				default:
					break;
			}
			break;

        case SDL_KEYUP:
            switch(_event.key.keysym.sym){

				case SDLK_w:
					if( y_velocity < 0 )
					y_velocity = 0;
					break;
				case SDLK_d:
					if( x_velocity > 0 )
					x_velocity = 0;
					break;
                case SDLK_s:
                    if( y_velocity > 0 )
					y_velocity = 0;
                    break;
				case SDLK_a:
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

	fourDirectionalMovementEvent->set_x_velocity(x_velocity);
	fourDirectionalMovementEvent->set_y_velocity(y_velocity);
	fourDirectionalMovementEvent->set_eventHasOccured(true);

	return fourDirectionalMovementEvent;
}

