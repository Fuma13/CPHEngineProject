#ifndef EngineControls_InputEvent_H
#define EngineControls_InputEvent_H

#include "InputEvent.h"
#include "ConfigurationEnums.h"

class EngineControls_InputEvent: public InputEvent 
{
private:
	EGameState gameState;

public:
	EngineControls_InputEvent() : InputEvent()
	{
		eventHasOccured = false;
	}

	EGameState get_gameStateRequest(){return gameState;}
	void set_gamestateRequest(EGameState gS) {gameState = gS;}
};

#endif