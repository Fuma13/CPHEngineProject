#include "RegionInformation.h"
#include <Winbase.h>//fore defrag
#include <Winnt.h>//for defrag
#include "SDL.h"

class Defragmentation{
private:
	~Defragmentation();
	Defragmentation();
	static Defragmentation* m_defrag;
	static unsigned long  size_segment_information;
	//variable will use in the decosnstructor for free the memory
	static LPDWORD thread;
public:
	static HANDLE h_thread[1];
	static Defragmentation* getInstance();
	static DWORD WINAPI defragmentation(LPVOID p);
	static RegionInformation* region_to_defrag;
	static Uint32 average_time_new_delete;
	static Uint32 max_time_defragmentation;
};