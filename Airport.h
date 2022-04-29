#ifndef AIRPORT
#define AIRPORT
#include "Cargo.h"
#include "Airplane.h"
class Airport
{
//friend  class Schedule;
private:
	string name;
	vector<OrdinaryCargo*> cargo;
	vector<Airplane> airplanes;
	vector<pair<string, int>> other_airports;
public:
	// add methods to erase cargo and plane, when plane has travel
	Airport(string name, vector<OrdinaryCargo*>& cargo,vector<Airplane>& airplanes,
		vector<pair<string, int>>& other_airports);
	string get_name() const;
	vector<OrdinaryCargo*> const& get_cargo_list () const; //unsafe method!
	vector<Airplane> const& get_airplanes_list() const;//unsafe method!
	vector<pair<string, int>> const& get_other_airports_list() const;
	void set_cargo_list(vector<OrdinaryCargo*> & cargo_);
	void set_airplanes_list(vector<Airplane>& airplanes_);
	void set_other_airports_list(vector<pair<string, int>>& other_airports_);

	int add_cargo(int* global_cargo_count, time_t global_time); // in final version change int to void 
	void add_airplane(Airplane& plane);
};
#endif;

