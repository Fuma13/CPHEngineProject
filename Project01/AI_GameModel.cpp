#include "AI_GameModel.h"
#define NULL 0
#include <iostream>
using namespace::std;

AI_GameModel * AI_GameModel::p_instance = NULL;

AI_GameModel::AI_GameModel()
{
	collision_player_car01 = false;
	collision_player_car02 = false;
	collision_car02_car01 = false;
}

AI_GameModel * getInstance();
	
AI_GameModel * AI_GameModel::getInstance()
{
	if(p_instance == NULL)
	{
		p_instance = new (EAllocationType::AI) AI_GameModel();
	}
	return p_instance;
}

void AI_GameModel::set_collision_with(const string & name_sender, const string & name_collision)
{
	if(name_sender == "cCar_01" && name_collision == "pCar_01")
	{collision_player_car01=true;}
	else if(name_sender == "cCar_02" && name_collision == "pCar_01")
	{collision_player_car02=true;}
	else if(name_sender == "cCar_01" && name_collision == "cCar_02")
	{collision_car02_car01=true;}
}

void AI_GameModel::set_NOcollision(const string & name_sender)
{
	if(name_sender == "cCar_01")
	{collision_player_car01=false;
	collision_car02_car01=false;}
	else if(name_sender == "cCar_02")
	{collision_player_car02=false;
	collision_car02_car01=false;}
	else if(name_sender == "pCar_01")
	{collision_player_car02=false;
	collision_player_car02=false;}
}

/*
void AI_GameModel::set_carMeshWidth(int w){carMeshWidth = w;}

void AI_GameModel::set_playerInfo(int x, int y, int velo)
{ player_x = x; player_y = y; player_velocity = velo;}

void AI_GameModel::set_npcInfo(int x, int y, int velo, int id)
{
	switch(id)
	{
		case 1:
			npc01_x = x;
			npc01_y = y;
			npc01_velocity = velo;
			break;
		case 2:
			npc02_x = x;
			npc02_y = y;
			npc02_velocity = velo;
			break;
		case 3:
			npc03_x = x;
			npc03_y = y;
			npc03_velocity = velo;
			break;
	}
}
	
bool AI_GameModel::get_playerOnSameLane(int id)
{
	int npc_x;
	switch(id)
	{		
		case 1:
			npc_x = npc01_x;
			break;
		case 2:
			npc_x = npc02_x;
			break;
		case 3:
			npc_x = npc03_x;
			break;
	}
	int lane_dif = player_x - npc_x;
	//absolut difference
	if(lane_dif<0){lane_dif = lane_dif*(-1);}
	if (lane_dif < carMeshWidth) return true;
	else return false;
}
*/

