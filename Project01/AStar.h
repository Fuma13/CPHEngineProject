#ifndef __AStar_H
#define __AStar_H

// dfg http://www.ai-blog.net/archives/000152.html
// fg http://newsgroups.derkeiler.com/Archive/Rec/rec.games.roguelike.development/2008-12/msg00128.html

class AStar
{

};


struct Node
{
	int c; // cost of node + predecessors
	int h; // heuristic estimate of distance to goal
	int f; // sum of predecessors, self + heuristic
};


#endif