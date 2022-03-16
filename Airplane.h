#ifndef AIRPLANE
#define AIRPLANE
#include "OrdinaryCargo.h"
class Airplane
{
private:
	int num;
	double capacity; //kg
	string home_ap;
	string other_ap;
	string dest_ap; // destination airport
	vector<OrdinaryCargo*> cargo;
	bool flight_status; //plane in flight or in airport? in flight == true
public:
	Airplane(int num, double capacity, vector<OrdinaryCargo*> &cargo,
		string home_ap, string other_ap, string dest_ap,
		bool flight_status);
	int get_num() const;
	double get_capacity() const;
	string get_dest_ap() const;
	string get_home_ap() const;
	string get_other_ap() const;
	bool get_flight_status() const;
	vector<OrdinaryCargo*> const& get_cargo_list() const;
	//
	bool add_cargo(double& free_payload, double cargo_mass, OrdinaryCargo* new_cargo);
	void change_flight_status(int i);
	void change_dest_ap(string str);
	void unload_cargo();
	string flight_direction();
};
bool pred_for_plane(Airplane& plane);
bool pred_for_plane_and_time(pair<Airplane, time_t>& plane_in_air);
#endif

