#include "OrdinaryCargo.h"
#include <iostream>
bool check_ap(string const& ap) {
	bool valid = true;
	if (ap.size() == 3) {
		for (int i = 0; i < 3; i++)
			if ((int)(ap[i]) < 65 || (int)(ap[i]) > 90)
				valid = false;
	}
	else { valid = false; }
	return valid;
}
OrdinaryCargo::OrdinaryCargo(int num, double weight, string dep_ap, string arr_ap, string curr_ap, string time)
{
	this->num = (num >= 0) ? (num) : (-1);
	this->weight = (weight > 0 && weight <= 100) ? (weight) : (-1);
	this->dep_ap = (check_ap(dep_ap)) ? (dep_ap) : ("invalid");
	this->arr_ap = (check_ap(arr_ap)) ? (arr_ap) : ("invalid");
	this->curr_ap = (check_ap(curr_ap)) ? (curr_ap) : ("invalid");
	// придумать проверку для поля time
	this->time = time;
}

OrdinaryCargo::~OrdinaryCargo(){}

int OrdinaryCargo::get_num() const { return num; }

double OrdinaryCargo::get_weight() const { return weight;}

string const& OrdinaryCargo::get_dep_ap() const { return dep_ap; }

string const& OrdinaryCargo::get_arr_ap() const { return arr_ap; }

string const& OrdinaryCargo::get_curr_ap() const { return curr_ap; }

string const& OrdinaryCargo::get_time() const { return time; }

void OrdinaryCargo::change_curr_ap(string & ap)
{
	string new_ap = ap;
	if (!check_ap(new_ap)) { std::cerr << "change_curr_ap|invalid string" << std::endl; }
	else { curr_ap = new_ap; }
}
