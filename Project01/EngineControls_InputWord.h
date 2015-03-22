#ifndef EngineControls_InputWord_H
#define EngineControls_InputWord_H

#include "InputWord.h"
#include "EngineControls_InputEvent.h"
#include "ConfigurationEnums.h"

class EngineControls_InputWord: public InputWord
{

private:	
	int gotoGameState;
	EGameState gameState;

	bool keypress_combination01_key01;
	bool keypress_combination01_key02;
	bool keypress_combination01_key03;
	bool keypress_combination01_key04;
	bool keypress_combination01_key05;

public:
	EngineControls_InputWord(int count_gameStates);

	InputEvent* update(SDL_Event _event);
};

#endif



