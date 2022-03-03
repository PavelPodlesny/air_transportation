#include "MainHeader.h"
time_t initial_time = time(0);
time_t current_time = initial_time;
bool check_ap(string const& ap) {
	bool valid = true;
	if (ap.size() == 3) {
		for (int i = 0; i < 3; i++)
			if ((int)(ap[i]) < 65 || (int)(ap[i]) > 90)
				valid = false;
	}
	else
		valid = false;
	return valid;
}
