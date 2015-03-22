#ifndef MemoryManagement__H
#define MemoryManagement__H

#pragma once //singletone
#include <tchar.h>
#include "Defragmentation.h"
#include <stdio.h>//imprt for overwrite the new operator
#include <stdlib.h> //for exit the program
#include <iostream>


class  MemoryManagement{
private:
	//declarations of variables
	static MemoryManagement* m_memory;
	static long page_size;
	static long  region_size;
	static unsigned long  size_segment_information;
	static Uint32 average_time_new;
	static Uint32 average_time_delete;
	static RegionInformation* reserved_memory;
	static Defragmentation* defrag;
	
	//methods
	MemoryManagement();
	static SegmentInformation*  createSegment(RegionInformation** reserved_memory,EAllocationType inf,size_t size);
	static long  initializePageSize();
	static long initializeRegionSize();
	static bool  getMemoryFromSystem(RegionInformation** region,size_t size,HANDLE base_reserved);
	static bool  reserveMemory(RegionInformation** region, unsigned long size_to_reserve);

public:
	static inline void  operator delete(void* obj,EAllocationType inf);
	static MemoryManagement* getInstance();
	static inline void* operator new (size_t size,EAllocationType inf);
};

#endif