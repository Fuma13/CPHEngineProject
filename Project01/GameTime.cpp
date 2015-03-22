#include "GameTime.h"
//do not want to need this here!
#define NULL 0

GameTime * GameTime::p_instance = NULL;

GameTime::GameTime()
{
	totalUpdatesSinceStart = 0;
}

GameTime * GameTime::getInstance()
{
	if(p_instance == NULL)
	{
		p_instance = new (EAllocationType::GAMEOBJECTS) GameTime();
	}
	return p_instance;
}

int GameTime::get_totalUpdatesSinceStart()
{
	return totalUpdatesSinceStart;
}

void GameTime::increase_totalUpdatesSinceStart()
{
	totalUpdatesSinceStart++;
}