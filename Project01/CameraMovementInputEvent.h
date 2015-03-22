#ifndef CameraMovementInputEvent_H
#define CameraMovementInputEvent_H

#include "InputEvent.h"
#include "Vector2.h"

class CameraMovementInputEvent: public InputEvent 
{
private:
	Vector2 position;
public:
	CameraMovementInputEvent() : InputEvent()
	{
		eventHasOccured = false;
		position = Vector2( 0.0F , 0.0F );
	}

	Vector2 get_current_position()
		{ return position;};
	void set_current_position(Vector2 current_pos)
		{ position = current_pos;}

};

#endif