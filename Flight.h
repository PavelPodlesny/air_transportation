#ifndef FLIGHT
#define FLIGHT
#include "MainHeader.h"
class Flight
{
private:
	string dep_ap;
	string arr_ap;
	time_t dep_time; //departure time
	time_t arr_time; //arrival time
	int airplane_num;
	bool erase;
public:
	Flight(string dep_ap = "", string arr_ap = "",
		time_t dep_time = 0, time_t arr_time = 0,
		int airplane_num = 0, bool erase = false);
	string get_dep_ap() const;
	string get_arr_ap() const;
	time_t get_dep_time() const;
	time_t get_arr_time() const;
	int get_airplane_num() const;
	//time_t time_in_flight() const;
	bool get_erase_value() const;
	void change_erase_value();
};
bool pred_for_flight(Flight const& flight);
#endif

