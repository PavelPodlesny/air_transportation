#ifndef  ORDINARY_CARGO
#define ORDINARY_CARGO

#include <string>
#include <iostream>
using std::string;
using std::stoi;

bool check_ap(string const& ap);
bool check_time(string const& ap);

class OrdinaryCargo
{
private:
	int num;
	double weight;
	string dep_ap, arr_ap, curr_ap;
	string time;
public:
	// constructor and destructor
	OrdinaryCargo(int num = 0, double weight = 20.0,
		string dep_ap = "SVO", string arr_ap = "MMK", string curr_ap = "SVO",
		string time = "20:00");
	~OrdinaryCargo();
	// methods of getting of the fields
	int get_num() const;
	double get_weight() const;
	string const& get_dep_ap() const;
	string const& get_arr_ap() const;
	string const& get_curr_ap() const;
	string const& get_time() const;
	// methods of changing of the fields
	void change_curr_ap(string &ap);
};
#endif

