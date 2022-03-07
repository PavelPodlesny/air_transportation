#include "OrdinaryCargo.h"

/*bool check_time(string const& t) {
	bool valid = true;
	if (t.size() == 5) {
		string h = t.substr(0, 2);
		int hi = stoi(h);
		string m = t.substr(3, 2);
		int mi = stoi(m);
		if (hi < 0 || hi>23 || mi<0 || mi>59 || t[2] !=':')
			valid = false;
	}
	else
		valid = false;
	return valid;
}*/


OrdinaryCargo::OrdinaryCargo(int num, double weight, string dep_ap, string arr_ap, string curr_ap, time_t time, bool erase)
{
	this->num = (num >= 0) ? (num) : (-1);
	this->weight = (weight > 0 && weight <= 100) ? (weight) : (-1);
	this->dep_ap = (check_ap(dep_ap)) ? (dep_ap) : ("invalid");
	this->arr_ap = (check_ap(arr_ap)) ? (arr_ap) : ("invalid");
	this->curr_ap = (check_ap(curr_ap)) ? (curr_ap) : ("invalid");
	this->time_ = (time > 0) ? (time) : (0);
	this->erase = erase;
}

OrdinaryCargo::~OrdinaryCargo(){}

int OrdinaryCargo::get_num() const { return num; }

double OrdinaryCargo::get_weight() const { return weight;}

string OrdinaryCargo::get_dep_ap() const { return dep_ap; }

string OrdinaryCargo::get_arr_ap() const { return arr_ap; }

string OrdinaryCargo::get_curr_ap() const { return curr_ap; }

time_t OrdinaryCargo::get_time() const {return time_;}

bool OrdinaryCargo::get_erase_value() const { return erase; }

void OrdinaryCargo::change_curr_ap(string & ap) // ap == airport
{
	string new_ap = ap;
	if (!check_ap(new_ap))
		std::cerr << "change_curr_ap|invalid string" << std::endl;
	else
		curr_ap = new_ap;
}

void OrdinaryCargo::change_erase_value() { erase = true; }

string OrdinaryCargo::check() const { return "parent"; }

/*void OrdinaryCargo::print_class() {
	char t[26];
	ctime_s(t, sizeof t, &time_);
	string str = dep_ap + " " + curr_ap + " " + arr_ap;
	cout << num << " " << weight << " " << str << " "<< t << endl;
}*/
bool OrdinaryCargo::operator< (OrdinaryCargo const& c) {
	if (weight < c.weight)
		return true;
	else
		return false;
}

bool OrdinaryCargo::operator>(OrdinaryCargo const& c)
{
	if (weight > c.weight)
		return true;
	else
		return false;
}

bool OrdinaryCargo::operator==(OrdinaryCargo const& c)
{
	if (weight == c.weight)
		return true;
	else
		return false;
}

UrgentCargo::UrgentCargo(int num, double weight, string dep_ap, string arr_ap, string curr_ap,
	time_t time_, time_t deadline, bool erase) :
	OrdinaryCargo(num, weight, dep_ap, arr_ap, curr_ap, time_, erase)
{
	this->deadline = (deadline > 0) ? (deadline) : (0);
}

time_t UrgentCargo::get_deadline() const { return deadline; }

UrgentCargo::~UrgentCargo() {}
string UrgentCargo::check() const { return "child"; }
;

bool pred(OrdinaryCargo& cargo) { return cargo.get_erase_value(); }
