#ifndef _AI_Manager_H
#define _AI_Manager_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "AI_Agent.h"

using namespace std;

class AI_Manager
{
private:
	static AI_Manager * p_instance;
	vector<AI_Agent*> ai_agents;

protected:
	AI_Manager();
public:

	void updateAgents();
	AI_Agent* get_AIAgent(const string & name);

	static AI_Manager * getInstance();
	~AI_Manager();
};

#endif