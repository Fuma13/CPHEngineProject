#include "AI_Manager.h"
#include "AI_GameModel.h"

#define NULL 0

AI_Manager * AI_Manager::p_instance = NULL;

AI_Manager::AI_Manager(){}

AI_Manager * getInstance();
	
AI_Manager * AI_Manager::getInstance()
{
	if(p_instance == NULL)
	{
		p_instance = new (EAllocationType::AI)  AI_Manager();
	}
	return p_instance;
}

AI_Agent* AI_Manager::get_AIAgent(const string & name)
{
	AI_Agent * agent = new (EAllocationType::AI)  AI_Agent(name);
	ai_agents.push_back(agent);
	return agent;
}

void AI_Manager::updateAgents()
{
	for (vector<AI_Agent*>::iterator it = ai_agents.begin(); it != ai_agents.end(); ++it) 
	{
		if(((*it)->name_t)=="cCar_01")
		{
			if(AI_GameModel::getInstance()->collision_player_car01)
			{(*it)->move_backwards = true;}
			else{(*it)->move_backwards = false;}
		}
	}
}