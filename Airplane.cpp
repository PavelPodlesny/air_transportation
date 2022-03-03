#include "Airplane.h"

Airplane::Airplane(int num, double capacity, vector<OrdinaryCargo>& ordinary_cargo,
	vector<UrgentCargo> &urgent_cargo, string home_ap, string dest_ap, bool in_flight/*, Flight& current_flight*/)
{
	this->num = (num > 0) ? (num) : (-1);
	this->capacity = (capacity > 0) ? (capacity) : (-1);
	this->ordinary_cargo = ordinary_cargo;
	this->urgent_cargo = urgent_cargo;
	this->home_ap = home_ap;
	this->dest_ap = dest_ap;
	this->in_flight = in_flight;
	//this->current_flight = current_flight;
}

int Airplane::get_num() const { return num;}

double Airplane::get_capacity() const {return capacity;}

string Airplane::get_dest_ap() const { return dest_ap; }

string Airplane::get_home_ap() const { return home_ap; }

bool Airplane::at_home(){
	bool ans;
	if (!in_flight && dest_ap != home_ap) ans = 1;
	else ans = 0;
	return ans;
}

bool Airplane::flight_status() { return in_flight; }

vector<OrdinaryCargo> const& Airplane::get_or_cargo_list() const {return ordinary_cargo;}

vector<UrgentCargo> const& Airplane::get_ur_cargo_list() const { return urgent_cargo; }

void Airplane::add_cargo(OrdinaryCargo& new_cargo) { ordinary_cargo.push_back(new_cargo); }

void Airplane::add_cargo(UrgentCargo& new_cargo) { urgent_cargo.push_back(new_cargo); }

void Airplane::in_flight_(int i){
	if (i == 1) in_flight = true;
	else in_flight = false;
}

void Airplane::change_dest_ap(string str) { dest_ap = str; }

bool pred_for_plane(Airplane& plane) { return plane.flight_status(); }
