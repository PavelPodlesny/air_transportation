#include "Airplane.h"

Airplane::Airplane(int num, double capacity, vector<OrdinaryCargo>& cargo,
	string home_ap, string other_ap, string dest_ap,
	bool flight_status)
{
	this->num = (num > 0) ? (num) : (-1);
	this->capacity = (capacity > 0) ? (capacity) : (-1);
	this->cargo = cargo;
	this->home_ap = (check_ap(home_ap)) ? (home_ap) : ("invalid");
	this->other_ap = (check_ap(other_ap)) ? (other_ap) : ("invalid");
	this->dest_ap = (check_ap(dest_ap)) ? (dest_ap) : ("invalid");;
	this->flight_status = flight_status;
	//this->current_flight = current_flight;
}

int Airplane::get_num() const { return num;}

double Airplane::get_capacity() const {return capacity;}

string Airplane::get_dest_ap() const { return dest_ap; }

string Airplane::get_home_ap() const { return home_ap; }

string Airplane::get_other_ap() const { return other_ap; }

bool Airplane::get_flight_status() const { return flight_status; }

vector<OrdinaryCargo> const& Airplane::get_cargo_list() const {return cargo;}

bool Airplane::add_cargo(double& free_payload, double cargo_mass, OrdinaryCargo& new_cargo) {
	if (free_payload - cargo_mass >= 0) {
		free_payload -= cargo_mass;
		cargo.push_back(new_cargo);
		return true;
	}
	else return false;
}

void Airplane::change_flight_status(int i){
	if (i == 1) flight_status = true;
	else flight_status = false;
}
void Airplane::change_dest_ap(string str) { dest_ap = (check_ap(str)) ? (str) : (dest_ap); }

void Airplane::unload_cargo(){
	cargo.clear();
}

string Airplane::flight_direction() {
	if (dest_ap == other_ap) return "direct";
	else return "revers";
}

bool pred_for_plane(Airplane& plane) { return plane.get_flight_status(); }

bool pred_for_plane_and_time(pair<Airplane, time_t>& plane) { return !plane.first.get_flight_status(); }
