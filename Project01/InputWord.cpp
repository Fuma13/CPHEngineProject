#include "InputWord.h"
#include "Root.h"

bool InputWord::first_call_this_update()
{
	int query = Root::getInstance()->mGameTime->get_totalUpdatesSinceStart();
	if (query == last_update_in_loop_nr)
	{
		cout << "second call" << endl;
		return false;
	}
	else
	{
		last_update_in_loop_nr = query;
		cout << "first call" << endl;
		return true;
	}
}