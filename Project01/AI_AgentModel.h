#ifndef AI_AgentModel_H
#define AI_AgentModel_H

using namespace::std;

class AI_AgentModel
{
private:

	bool playerOnSameLane;
	bool playerApproaching;

public:
	AI_AgentModel();

	bool get_playerOnSameLane(){return playerOnSameLane;}
	bool get_playerApproaching(){return playerApproaching;}

};

#endif
