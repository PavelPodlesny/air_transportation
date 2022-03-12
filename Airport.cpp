#include "Airport.h"

Airport::Airport(string name, vector<OrdinaryCargo>& cargo,
	vector<Airplane>& airplanes, vector<pair<string, int>>& other_airports){
	this->name = (check_ap(name)) ? (name) : ("invalid");
	this->cargo = cargo;
	this->airplanes = airplanes;
	this->other_airports = other_airports;
}

string Airport::get_name() const { return name; }

vector<OrdinaryCargo> const& Airport::get_cargo_list() { return cargo; }

vector<Airplane> const& Airport::get_airplanes_list() { return airplanes; }

vector<pair<string, int>> const& Airport::get_other_airports_list() { return other_airports; }

void Airport::set_cargo_list(vector<OrdinaryCargo>& cargo_) { cargo = cargo_; }

void Airport::set_airplanes_list(vector<Airplane>& airplanes_) { airplanes = airplanes_; }

void Airport::set_other_airports_list(vector<pair<string, int>>& other_airports_) { other_airports = other_airports_; }

void Airport::add_cargo(int& global_cargo_count, time_t global_time){
	srand(time(0));
	string arrival_airport;
	double cargo_weight;
	int count_cargo = (rand() % 5) + 1;
	int count_or_cargo = (rand() % 5) + 1;
	int count_ur_cargo = count_cargo - count_or_cargo;
	for (int i = 0; i < count_or_cargo; ++i) {
		cargo_weight = (rand() % 61) + 40;
		arrival_airport = other_airports[rand()%(other_airports.size())].first; //other
		OrdinaryCargo new_cargo(global_cargo_count, cargo_weight,
			name, arrival_airport, name, global_time);
		cargo.push_back(new_cargo);
		global_cargo_count++;
	}
	time_t time_deadline;
	for (int i = 0; i < count_ur_cargo; ++i) {
		cargo_weight = (rand() % 61) + 40;
		arrival_airport = other_airports[rand() % (other_airports.size())].first;
		time_deadline = (time_t)(3600 * (rand() % 3 + 4));
		UrgentCargo new_cargo(global_cargo_count, cargo_weight,
			name, arrival_airport, name, global_time,
			time_deadline);
		cargo.push_back(new_cargo);
		global_cargo_count++;
	}
}
void Airport::add_airplane(Airplane& plane) { airplanes.push_back(plane); }
/*void Airport::add_flight(Airplane& plane, string arr_ap, time_t current_time) {
	time_t time_in_flight = (time_t)(4 * 3600), time_in_arr_ap = (time_t)(3600);
	int plane_num = plane.get_num();
	Flight forward_flight(name, arr_ap, current_time, current_time+time_in_flight, plane_num);
	Flight return_flight(arr_ap, name, current_time + time_in_flight + time_in_arr_ap,
	current_time + 2 * time_in_flight + time_in_arr_ap, plane_num);
	schedule.push_back(forward_flight);
	schedule.push_back(return_flight);
}

void Airport::complete_flight(Flight& flight){
	vector<Flight>::iterator i = schedule.begin(),
		end = schedule.end();
	int num = (*i).get_airplane_num(), 
	flight_num = flight.get_airplane_num();

	while (i != end && num != flight_num) {
		++i;
		num = (*i).get_airplane_num();
	}
	if (i == end)
		std::cerr << "Aiport.cpp|complete_flight|flight_is_not_found" << endl;
	else
		schedule.erase(i);
}*/
