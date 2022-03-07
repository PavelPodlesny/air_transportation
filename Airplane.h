#ifndef AIRPLANE
#define AIRPLANE
#include "OrdinaryCargo.h"
#include "Flight.h"
class Airplane
{
private:
	int num;
	double capacity;
	string home_ap;
	string other_ap;
	string dest_ap; // destination airport
	//Flight current_flight;
	vector<OrdinaryCargo> ordinary_cargo;
	vector<UrgentCargo> urgent_cargo;
	bool in_flight;
	bool reverse_flight;
public:
	Airplane(int num, double capacity, vector<OrdinaryCargo> &ordinary_cargo,
		vector<UrgentCargo> &urgent_cargo, string home_ap, string other_ap, string dest_ap,
		bool in_flight, bool reverse_flight);
	int get_num() const;
	double get_capacity() const;
	string get_dest_ap() const;
	string get_home_ap() const;
	string get_other_ap() const;
	bool at_home();
	bool flight_status();
	bool flight_is_reverse();
	vector<OrdinaryCargo> const& get_or_cargo_list() const; // made for urgent
	vector<UrgentCargo> const& get_ur_cargo_list() const;
	//Flight const& get_current_flight() const;
	void add_cargo(OrdinaryCargo& new_cargo);
	void add_cargo(UrgentCargo& new_cargo);
	void in_flight_(int i);
	void reverse_flight_(int i);
	void change_dest_ap(string str);
	void unload_cargo();
	//void set_current_flight(Flight &new_flight);
	//void print_airplane_info();
};
bool pred_for_plane(Airplane& plane);
bool pred_for_plane_and_time(pair<Airplane, time_t>& plane);
#endif

