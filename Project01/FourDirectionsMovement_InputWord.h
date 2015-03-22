#ifndef FourDirectionsMovement_InputWord_H
#define FourDirectionsMovement_InputWord_H

#include "InputWord.h"
#include "FourDirectionsMovement_InputEvent.h"

class FourDirectionsMovement_InputWord: public InputWord
{

private:
	float x_velocity;
	float y_velocity;

public:
	FourDirectionsMovement_InputWord(int count_gameStates);

	InputEvent* update(SDL_Event _event);

};

#endif



