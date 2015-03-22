#ifndef Combo_01_InputEvent_H
#define Combo_01_InputEvent_H

#include "InputEvent.h"

class Combo_01_InputEvent: public InputEvent
{
public:
	#pragma message ("XXXXXXXXXXXXXXXXXXXXXXX Combo_01_InputEvent included")

	Combo_01_InputEvent() : InputEvent()
	{
		eventHasOccured = false;
	}
};
#endif