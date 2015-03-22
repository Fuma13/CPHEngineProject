#ifndef CarMovement_InputWord_H
#define CarMovement_InputWord_H

#include "InputWord.h"
#include "CarMovement_InputEvent.h"

class CarMovement_InputWord: public InputWord
{
private:	
	float x_velocity;
	float y_velocity;

public:

	CarMovement_InputWord(int count_gameStates);
	
	InputEvent* update(SDL_Event _event);
};

#endif



