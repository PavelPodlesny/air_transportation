#ifndef SCHEDULE
#define SCHEDULE
#include "Airport.h"
#include "Airplane.h"
#include "Flight.h"
class Schedule
{
private:
	vector<Airport> airports;
	vector<Flight> schedule;
	vector<pair<Airplane, time_t>> planes_in_air;
public:
	Schedule(vector<Airport>& airports, vector<Flight>& schedule, vector<pair<Airplane, time_t>>& planes_in_air);
	void add_flight(string dep_ap, string arr_ap, time_t dep_time, time_t arr_time,
		int plane_num);
	void add_plane(Airplane& plane, time_t dep_time, time_t arr_time);
	void landing(Airplane& plane);
	void check_arrival_time();
	void del_flight(int plane_num);
};
#endif

