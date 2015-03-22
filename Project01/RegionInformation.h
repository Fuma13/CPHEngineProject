
#include <windows.h>
#include "SegmentInformation.h";

typedef struct _RegionInformation{
	
	//information about the next position of the segment
	struct _RegionInformation* next_region;
	//used if the segment is free pointer backward to the position before
	struct _RegionInformation* previous_region;
	//size of the reserved memory
	unsigned long reserve_size;
	//top commited
	HANDLE top_committed;
	HANDLE actual_committed;
	HANDLE region_start_position;
	//top reserved
	HANDLE top_reserved;
	//vector<SegmentInformation*> free_segments;
	short int count_of_objects;
	short int maximum_free_dimension;
	struct _SegmentInformation* last_free_segment;
}RegionInformation;


