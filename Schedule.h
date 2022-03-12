#ifndef SCHEDULE
#define SCHEDULE
#include "Airport.h"
#include "Flight.h"
class Schedule
{
private:
	vector<Airport> airports;
	vector<Flight> schedule;
	vector<pair<Airplane, time_t>> planes_in_air; //time_t == time in flight
public:
	Schedule(vector<Airport>& airports, vector<Flight>& schedule, vector<pair<Airplane, time_t>>& planes_in_air);
	void add_flight(string dep_ap, string arr_ap, time_t dep_time, time_t arr_time,
		int plane_num);
	void del_flight(int plane_num);
	void add_plane(Airplane& plane, time_t time_in_flight);
	void add_cargo(int& global_cargo_count, time_t global_time); // in final version change int to void 
	void sending_planes(time_t global_time);
	void landing_plane(Airplane& plane);
	void check_arrival_time();
	void print();
	vector<Airport> const& get_airports_list();
	vector<Flight> const& get_flights_list();
	vector<pair<Airplane, time_t>> const& get_planes_in_air_list();
	
};
#endif

