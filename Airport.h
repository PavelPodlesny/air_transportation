#ifndef AIRPORT
#define AIRPORT
#include "OrdinaryCargo.h"
#include "Airplane.h"
class Airport
{
private:
	string name;
	vector<OrdinaryCargo> ordinary_cargo;
	vector<UrgentCargo> urgent_cargo;
	vector<Airplane> airplanes;
public:
	// add methods to erase cargo and plane, when plane has travel
	Airport(string name, vector<OrdinaryCargo>& ordinary_cargo,
		vector<UrgentCargo>& urgent_cargo, vector<Airplane>& airplanes);
	string get_name() const;
	vector<OrdinaryCargo> const& get_list_ordinary_cargo(); //unsafe method!
	vector<UrgentCargo> const& get_list_urgent_cargo();//unsafe method!
	vector<Airplane> const& get_list_airplanes();//unsafe method!
	void set_list_ordinary_cargo(vector<OrdinaryCargo> & or_cargo);
	void set_list_urgent_cargo(vector<UrgentCargo> & ur_cargo);
	void set_list_airplanes(vector<Airplane>& list_airplanes);

	void add_cargo(int& global_cargo_count, time_t& global_time); //!
	void cargo_to_plane();

};
#endif;

