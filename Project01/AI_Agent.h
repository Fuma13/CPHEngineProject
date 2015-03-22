#ifndef AI_Agent_H
#define AI_Agent_H

#include<string>
#include "MemoryManager.h"
class AI_AgentModel;

using namespace::std;

class AI_Agent
{
private:
	
	AI_AgentModel * m_AgentModel;
public:
	string name_t;
	bool move_backwards;

	AI_Agent(const string & name)
	{
		name_t = name;
		move_backwards = false;
	}
};

#endif
