#include "Airport.h"

Airport::Airport(string name, vector<OrdinaryCargo>& ordinary_cargo, vector<UrgentCargo>& urgent_cargo,
	vector<Airplane>& airplanes, vector<pair<string, int>>& other_airports){
	this->name = name;
	this->ordinary_cargo = ordinary_cargo;
	this->urgent_cargo = urgent_cargo;
	this->airplanes = airplanes;
	this->other_airports = other_airports;
}

string Airport::get_name() const { return name; }

vector<OrdinaryCargo> const& Airport::get_list_ordinary_cargo() { return ordinary_cargo; }

vector<UrgentCargo> const& Airport::get_list_urgent_cargo() { return urgent_cargo; }

vector<Airplane> const& Airport::get_list_airplanes() { return airplanes; }

void Airport::set_list_ordinary_cargo(vector<OrdinaryCargo>& or_cargo){ordinary_cargo = or_cargo;}

void Airport::set_list_urgent_cargo(vector<UrgentCargo>& ur_cargo) { urgent_cargo = ur_cargo; }

void Airport::set_list_airplanes(vector<Airplane>& list_airplanes) { airplanes = list_airplanes; }

void Airport::set_list_other_airports(vector<pair<string, int>>& list_other_airports) { other_airports = list_other_airports; }

void Airport::add_cargo(int& global_cargo_count, time_t global_time){
	srand(time(NULL));
	string arrival_airport;
	double cargo_weight;
	int count_cargo = (rand() % 5) + 1;
	int count_or_cargo = (rand() % 5) + 1;
	int count_ur_cargo = count_cargo - count_or_cargo;
	for (int i = 0; i < count_or_cargo; ++i) {
		cargo_weight = (rand() % 61) + 40;
		arrival_airport = other_airports[rand()%(other_airports.size())].first; //other
		OrdinaryCargo cargo(global_cargo_count, cargo_weight,
			name, arrival_airport, name, global_time);
		ordinary_cargo.push_back(cargo);
		global_cargo_count++;
	}
	time_t time_deadline;
	for (int i = 0; i < count_ur_cargo; ++i) {
		cargo_weight = (rand() % 61) + 40;
		arrival_airport = other_airports[rand() % (other_airports.size())].first;
		time_deadline = (time_t)(3600 * (rand() % 3 + 4));
		UrgentCargo cargo(global_cargo_count, cargo_weight,
			name, arrival_airport, name, global_time,
			time_deadline);
		urgent_cargo.push_back(cargo);
		global_cargo_count++;
	}

}

void Airport::cargo_to_plane(){
	vector<Airplane>::iterator i = airplanes.begin(), end = airplanes.end();
	for (i; i != end; ++i) {
		double payload = ((*i).get_capacity()), original_payload = payload;
		string destination_airport = (*i).get_dest_ap(), arrival_aiport;
		bool overflow = false;
		sort(urgent_cargo.rbegin(), urgent_cargo.rend());
		vector<UrgentCargo>::iterator uc = urgent_cargo.begin(), uc_end = urgent_cargo.end();
		while (uc != uc_end && !overflow) {
			arrival_aiport = (*uc).get_arr_ap();
			if (destination_airport == arrival_aiport) {
				double mass = (*uc).get_weight();
				if ((payload - mass) >= 0) {
					(*i).add_cargo((*uc));
					payload -= mass;
					(*uc).change_erase_value();
				}
				else overflow = true;
			}
			++uc;
		}
		urgent_cargo.erase(std::remove_if(urgent_cargo.begin(), urgent_cargo.end(), pred), urgent_cargo.end()); //!
		if (overflow == true && payload <= (0.25 * original_payload)) { (*i).in_flight_(1);/*start flight*/ }
		else {
			overflow = false;
			sort(ordinary_cargo.rbegin(), ordinary_cargo.rend());
			vector<OrdinaryCargo>::iterator oc = ordinary_cargo.begin(), oc_end = ordinary_cargo.end();
			while (oc != oc_end && !overflow) {
				arrival_aiport = (*oc).get_arr_ap();
				if (destination_airport == arrival_aiport) {
					double mass = (*oc).get_weight();
					if ((payload - mass) >= 0) {
						(*i).add_cargo((*oc));
						payload -= mass;
						(*oc).change_erase_value();
					}
					else overflow = true;
				}
				++oc;
			}
			ordinary_cargo.erase(std::remove_if(ordinary_cargo.begin(), ordinary_cargo.end(), pred), ordinary_cargo.end());
			if (payload <= (0.25 * original_payload)) { (*i).in_flight_(1);/*start flight*/ }
		}
	}
	//airplanes.erase(std::remove_if(airplanes.begin(), airplanes.end(), pred_for_plane), airplanes.end());
	//if the airplane took off, move it to "plane_in_flight" list
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
