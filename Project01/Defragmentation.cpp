#include "Defragmentation.h"

Uint32 Defragmentation::average_time_new_delete=0;
Uint32 Defragmentation::max_time_defragmentation=9999;
Defragmentation* Defragmentation::m_defrag=nullptr;
HANDLE Defragmentation::h_thread[1] = {nullptr};
LPDWORD Defragmentation::thread = nullptr;
RegionInformation* Defragmentation::region_to_defrag(nullptr);
unsigned long  Defragmentation::size_segment_information=sizeof(SegmentInformation);

Defragmentation::Defragmentation(){

	h_thread[0] = CreateThread(NULL,0,defragmentation,nullptr,CREATE_SUSPENDED,thread);
	
}

Defragmentation::~Defragmentation(){
	
	CloseHandle(thread);
}


Defragmentation * Defragmentation::getInstance()
{
	if(m_defrag == NULL)
	{
		m_defrag = new Defragmentation();
	}
	return m_defrag;
}

DWORD WINAPI Defragmentation::defragmentation(LPVOID p){
	Uint32 temp_time=0;
	//variable for see how many time i have for defragment
	Uint32 temp_def = 0;
	size_t size=0;
	Uint32 time = 0;
	//RegionInformation* region_to_defrag = reinterpret_cast<RegionInformation*>(p);
	SegmentInformation* temp_segment = nullptr;
	Uint32 debug=0;
	
	//std::cout<<"ciao"<<std::endl;
	


	temp_segment = region_to_defrag->last_free_segment;	
	temp_def = SDL_GetTicks() + average_time_new_delete;
	while (SDL_GetTicks() < temp_def)
	{
		if(region_to_defrag !=nullptr)
		{
			if(temp_segment != nullptr)
			{
				SegmentInformation* segment_to_move = (SegmentInformation*)((long)temp_segment->object_start_position + temp_segment->dimension);
				//check if i'm in the position of the top commited memory
				if(((HANDLE)((long)temp_segment->object_start_position + temp_segment->dimension)!= region_to_defrag->actual_committed || ((long)region_to_defrag->top_reserved - (long)region_to_defrag->actual_committed)>=size_segment_information) && segment_to_move != region_to_defrag->top_reserved)
				{
					if (segment_to_move->is_available == USED)
					{
						
						SegmentInformation temp_segment_informations = *temp_segment;
					
						size_t dimension_new_free_segment = (unsigned)(segment_to_move->dimension - temp_segment->dimension); 
						//move the memory in the position of the free segment
						MoveMemory(temp_segment,segment_to_move,segment_to_move->dimension + sizeof(size_segment_information));
						
						//update the informations inside the segment where i put all the segment moved. i need to update only 2 informations because 
						//i need to point to the previous object start position and the previous segment start position (for the movement)
						temp_segment->object_start_position = temp_segment_informations.object_start_position;
						temp_segment->segment_start_position=temp_segment_informations.segment_start_position;
						
						//clear the memorry used by the previous object that is not used 
						ZeroMemory((HANDLE)((long)temp_segment->object_start_position+temp_segment->dimension),dimension_new_free_segment + sizeof(size_segment_information));
						//create the new segment inside the new free zone that the movement leave	
						SegmentInformation* new_segment;
						new_segment = (SegmentInformation*)((long)segment_to_move->object_start_position + segment_to_move->dimension);
						new_segment->allocation_type = EAllocationType::NO_ASSIGNED;
						new_segment->is_available = EIsAvailable::FREE;
						new_segment->dimension = dimension_new_free_segment;
						new_segment->next_segment = temp_segment_informations.next_segment;
						new_segment->previous_segment=temp_segment_informations.previous_segment;
						new_segment->region_position = temp_segment_informations.region_position;
						new_segment->segment_start_position = new_segment;
						//check if the size of the new free segment is more then only the size for the segment informations
						if(dimension_new_free_segment>0){
							new_segment->object_start_position = (HANDLE)((long)new_segment->segment_start_position + size_segment_information);
						}else{
							//there isn't enough space for another object but only for the structure
							new_segment->object_start_position=nullptr;
						}
						//check if this new free size is more big than the other already present inside the region
						if(region_to_defrag->maximum_free_dimension < temp_segment->dimension){
	
							region_to_defrag->maximum_free_dimension = temp_segment->dimension;
						}

					}else{
						//there is a free segment after this so i join the sections
						temp_segment->dimension += segment_to_move->dimension;
						temp_segment->previous_segment = segment_to_move->previous_segment;
						segment_to_move = nullptr;
					}
				}
				
				//continue with other segments
				temp_segment = temp_segment->previous_segment;
			}
			else
			{
				//i know it was defragmented
			
				region_to_defrag = region_to_defrag->previous_region;
				//initialize the temp_segment with the new free segment of the new free region
				if(region_to_defrag!=nullptr)
					temp_segment = region_to_defrag->last_free_segment;	
			}

		//if i'm in the first region that don't point nothing
		}
		else
		{
			
			break;
		}
	}
	
	if(max_time_defragmentation < temp_time){
	
		max_time_defragmentation = temp_time;
	}
	return 0;

}