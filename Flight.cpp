#include "Flight.h"

Flight::Flight(string dep_ap, string arr_ap,
	time_t dep_time, time_t arr_time, int airplane_num) {
	this->dep_ap = (check_ap(dep_ap)) ? (dep_ap) : ("invalid");
	this->arr_ap = (check_ap(arr_ap)) ? (arr_ap) : ("invalid");
	this->dep_time = (dep_time > 0) ? (dep_time) : (0);
	this->arr_time = (arr_time > 0) ? (arr_time) : (0);
	this->airplane_num = (airplane_num > 0) ? (airplane_num) : (-1);
}

string Flight::get_dep_ap() const { return dep_ap; }

string Flight::get_arr_ap() const { return arr_ap; }

time_t Flight::get_dep_time() const { return dep_time; }

time_t Flight::get_arr_time() const { return arr_time; }

int Flight::get_airplane_num() const { return airplane_num; }

time_t Flight::time_in_flight() const { return arr_time - dep_time; }
