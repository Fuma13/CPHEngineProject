#ifndef Combo_01_InputWord_H
#define Combo_01_InputWord_H

#include "InputWord.h"
#include "Combo_01_InputEvent.h"

class Combo_01_InputWord: public InputWord
{
public:
	#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX Combo_01_InputWord included")
	Combo_01_InputWord(int count_gameStates) : InputWord(count_gameStates){}

	InputEvent* update(SDL_Event _event)
	{

		Combo_01_InputEvent* cameraMovementEvent = new Combo_01_InputEvent();

		event_current = _event;

		 switch(_event.type)
		{
	 
			default:
				// TODO warn that an event that is not useful has been sent, and this should not happen!!!
				cout << "WARNING: An InputWord has received an input event that is not handled in the switch/case" << endl;
				break;
		}

		 return cameraMovementEvent;
	}
};
#endif