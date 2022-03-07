#include "Schedule.h"

Schedule::Schedule(vector<Airport>& airports, vector<Flight>& schedule, vector<pair<Airplane,
	time_t>>& planes_in_air)
{
	this->schedule = schedule;
	this->planes_in_air = planes_in_air;
	this->airports = airports;
}

void Schedule::add_flight(string dep_ap, string arr_ap, time_t dep_time, time_t arr_time, int plane_num)
{
	Flight flight(dep_ap, arr_ap, dep_time, arr_time, plane_num);
	schedule.push_back(flight);
}

void Schedule::add_plane(Airplane& plane, time_t dep_time, time_t arr_time)
{
	pair<Airplane, time_t> air_travel = {plane, arr_time-dep_time};
	planes_in_air.push_back(air_travel);
}

void Schedule::landing(Airplane& plane){
	plane.in_flight_(0);
	plane.unload_cargo();
	string destination_airport = plane.get_dest_ap();
	auto i = airports.begin(), end = airports.end();
	while (i != end && destination_airport != (*i).get_name()) ++i;
	if (i == end) std::cerr << "Schedule|landing|airpirt isn't found";
	else {
		if (plane.get_home_ap() == destination_airport) plane.change_dest_ap(plane.get_other_ap());
		else plane.change_dest_ap(plane.get_home_ap());
		(*i).add_airplane(plane);
		this->del_flight(plane.get_num());
	}
}

void Schedule::check_arrival_time(){
	auto i = planes_in_air.begin(), end = planes_in_air.end();
	for (i; i != end; ++i) {
		(*i).second -= (time_t)(3600);
		if ((*i).second <= 0) landing((*i).first);
	}
	planes_in_air.erase(std::remove_if(planes_in_air.begin(), planes_in_air.end(), pred_for_plane_and_time), planes_in_air.end());
	//urgent_cargo.erase(std::remove_if(urgent_cargo.begin(), urgent_cargo.end(), pred), urgent_cargo.end());
}

void Schedule::del_flight(int plane_num)
{
	vector<Flight>::iterator i = schedule.begin(), end = schedule.end();
	while (i != end && plane_num != (*i).get_airplane_num()) ++i;
	if (i == end) std::cerr << "Schedule|del_flight|plane isn't found" << endl;
	else schedule.erase(i);
}

