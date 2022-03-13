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

void Schedule::add_plane(Airplane& plane, time_t time_in_flight)
{
	pair<Airplane, time_t> air_travel = {plane, time_in_flight};
	planes_in_air.push_back(air_travel);
}

void Schedule::add_cargo(int& global_cargo_count, time_t global_time){
	int cargo_count=0;
	for (auto i = airports.begin(); i != airports.end(); ++i) {
		(*i).add_cargo(global_cargo_count, global_time);
	}
}

void Schedule::landing_plane(Airplane& plane){
	plane.change_flight_status(0);
	plane.unload_cargo();
	auto i = airports.begin(), end = airports.end();
	while (i != end && plane.get_dest_ap() != (*i).get_name()) ++i;
	if (i == end) std::cerr << "Schedule|landing|airpirt isn't found";
	else {
		if (plane.get_home_ap() == plane.get_dest_ap()) plane.change_dest_ap(plane.get_other_ap());
		else plane.change_dest_ap(plane.get_home_ap());
		(*i).add_airplane(plane);
		del_flight(plane.get_num());
	}
}

void Schedule::check_arrival_time(){
	auto i = planes_in_air.begin(), end = planes_in_air.end();
	for (i; i != end; ++i) {
		(*i).second -= (time_t)(3600);
		if ((*i).second <= 0) landing_plane((*i).first);
	}
	planes_in_air.erase(std::remove_if(planes_in_air.begin(), planes_in_air.end(), pred_for_plane_and_time), planes_in_air.end());
	//urgent_cargo.erase(std::remove_if(urgent_cargo.begin(), urgent_cargo.end(), pred), urgent_cargo.end());
}

void Schedule::print() {
	int count = 1;
	cout << setw(9) << left << "Flight #";
	cout << setw(19) << "Departure airport";
	cout << setw(15) << right << "Arrival airport" << " ";
	cout << setw(5) << " " << "Departure time" << setw(5) << " ";
	cout << "	";
	cout << setw(6) << " " << "Arrival time" << setw(6) << " ";
	cout << "	";
	cout << setw(12) << "Plane number" << endl;
	char buf[26];
	for (auto i = schedule.begin(); i != schedule.end(); ++i) {
		cout << setw(9) << left << count;
		cout << setw(8) << " " << (*i).get_dep_ap() << setw(8) << " ";
		cout << setw(6) << " " << (*i).get_arr_ap() << setw(7) << " ";
		time_t time_ = (*i).get_dep_time();
		ctime_s(buf, sizeof(buf), &time_); buf[24] = '\0';
		cout << setw(24) << buf << "	";
		time_ = (*i).get_arr_time();
		ctime_s(buf, sizeof(buf), &time_); buf[24] = '\0';
		cout << setw(24) << buf << "	";
		cout << setw(5) << " " << (*i).get_airplane_num() << setw(5) << " " <<endl;
		count++;
	}
}

vector<Airport> const& Schedule::get_airports_list() { return airports; }

vector<Flight> const& Schedule::get_flights_list() { return schedule; }

vector<pair<Airplane, time_t>> const& Schedule::get_planes_in_air_list() { return planes_in_air; }

void Schedule::del_flight(int plane_num)
{
	auto i = schedule.begin(), end = schedule.end();
	while (i != end && plane_num != (*i).get_airplane_num()) ++i;
	if (i == end) std::cerr << "Schedule|del_flight|plane isn't found" << endl;
	else schedule.erase(i);
}
void Schedule::sending_planes(time_t global_time) {
	for(auto airport_ = airports.begin(); airport_!=airports.end(); ++airport_){
	vector <Airplane> airplanes = (*airport_).get_airplanes_list();
	vector <OrdinaryCargo> cargo = (*airport_).get_cargo_list();
	for (auto i = airplanes.begin(); i != airplanes.end(); ++i) {
		double free_payload = ((*i).get_capacity()), initial_payload = free_payload;
		string destination_airport = (*i).get_dest_ap();
		bool overflow = false;
		sort(cargo.begin(), cargo.end());
		auto c = cargo.begin(), c_end = cargo.end();
		while (c != c_end && !overflow) { // cycle by urgent cargo
			if ((*c).check() == "urgent" && (*c).get_arr_ap() == destination_airport) {
				if ((*i).add_cargo(free_payload, (*c).get_weight(), *c)) { (*c).change_erase_value(); }
				else overflow = true;
			}
			++c;
		}
		if (free_payload <= (0.25 * initial_payload)) {
			time_t time_in_flight = 0;
			(*i).change_flight_status(1);
			//start flight
			vector<pair<string, int>> other_airports = (*airport_).get_other_airports_list();
			auto j = other_airports.begin(), j_end = other_airports.end();
			while (j != j_end && destination_airport != (*j).first) { ++j; }
			if (j == j_end) std::cerr << "Schedule|sending_planes|destination airport isn't found" << endl;
			else {
				time_in_flight = (time_t)((*j).second * 3600);
				add_flight((*airport_).get_name(), destination_airport,
					global_time, global_time + time_in_flight, (*i).get_num());
				add_plane((*i), time_in_flight);
			}
			//start flight
		}
		else {
			overflow = false;
			c = cargo.begin(); c_end = cargo.end();
			while (c != c_end && !overflow) {
				if ((*c).check() == "ordinary" && (*c).get_arr_ap() == destination_airport) {
					if ((*i).add_cargo(free_payload, (*c).get_weight(), *c)) { (*c).change_erase_value(); }
					else overflow = true;
				}
				++c;
			}
			if (free_payload <= (0.25 * initial_payload)) {
				time_t time_in_flight = 0;
				(*i).change_flight_status(1);
				//start flight
				vector<pair<string, int>> other_airports = (*airport_).get_other_airports_list();
				auto j = other_airports.begin(), j_end = other_airports.end();
				while (j != j_end && destination_airport != (*j).first) { ++j; }
				if (j == j_end) std::cerr << "Schedule|sending_planes|destination airport isn't found" << endl;
				else {
					time_in_flight = (time_t)((*j).second * 3600);
					add_flight((*airport_).get_name(), destination_airport,
						global_time, global_time + time_in_flight, (*i).get_num());
					add_plane((*i), time_in_flight);
				}
				//start flight
			}
		}
		cargo.erase(std::remove_if(cargo.begin(), cargo.end(), pred), cargo.end()); //!

	}
	airplanes.erase(std::remove_if(airplanes.begin(), airplanes.end(), pred_for_plane), airplanes.end());
	//if the airplane took off, move it to "plane_in_flight" list
	(*airport_).set_airplanes_list(airplanes);
	(*airport_).set_cargo_list(cargo);
	}
}
