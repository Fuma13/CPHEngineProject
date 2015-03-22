#ifndef CameraMovementInputWord_H
#define CameraMovementInputWord_H

#include "InputWord.h"
#include "Vector2.h"
#include "CameraMovementInputEvent.h"

class CameraMovementInputWord: public InputWord
{

public:
	CameraMovementInputWord(int count_gameStates);

	InputEvent* update(SDL_Event _event);
	
};

#endif



