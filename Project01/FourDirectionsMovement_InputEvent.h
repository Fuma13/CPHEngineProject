#ifndef FourDirectionsMovement_InputEvent_H
#define FourDirectionsMovement_InputEvent_H

#include "InputEvent.h"

class FourDirectionsMovement_InputEvent: public InputEvent 
{
private:
	float x_velocity;
	float y_velocity;

public:
	FourDirectionsMovement_InputEvent() : InputEvent()
	{
		eventHasOccured = false;
	}
	float get_x_velocity() {return x_velocity;}
	void set_x_velocity(float pass) {x_velocity = pass;}
	float get_y_velocity() {return y_velocity;}
	void set_y_velocity(float pass) {y_velocity= pass;}


};

#endif