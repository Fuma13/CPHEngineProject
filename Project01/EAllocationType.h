/*
	Types of objects that the memory can allocate
	and if the block is a free block or a used block
*/
enum EAllocationType
{	
		NO_ASSIGNED,
		ROOT,
		PHYSICS,
		AI,
		RENDERING,
		NODES,
		GAME_LOOP,
		INPUT_MANAGER,
		MEMORYMANAGEMENT,
		GAMEOBJECTS,
};


