#include "Cargo.h"
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
	bool error_flag = 0;
	if (num <= 0) error_flag = 1;
	if (weight < 0 || weight > 100) error_flag = 1;
	if (!check_ap(dep_ap)) error_flag = 1;
	if (!check_ap(arr_ap)) error_flag = 1;
	if (!check_ap(curr_ap)) error_flag = 1;
	if (time < 0) error_flag = 1;
	if (error_flag) throw std::exception("OrdinaryCargo|invalid constructor's parameters");
	this->num = num;
	this->weight = weight;
	this->dep_ap = dep_ap;
	this->arr_ap = arr_ap;
	this->curr_ap = curr_ap;
	this->time_ = time;
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
	if (!check_ap(new_ap)) std::cerr << "OrdinaryCargo|change_curr_ap|invalid string" << std::endl;
	else curr_ap = new_ap;
}

void OrdinaryCargo::change_erase_value() { erase = true; }

string OrdinaryCargo::check() const { return "ordinary"; }

/*void OrdinaryCargo::print_class() {
	char t[26];
	ctime_s(t, sizeof t, &time_);
	string str = dep_ap + " " + curr_ap + " " + arr_ap;
	cout << num << " " << weight << " " << str << " "<< t << endl;
}*/
bool OrdinaryCargo::operator< (OrdinaryCargo const& c) const {
	if (weight < c.weight)
		return true;
	else
		return false;
}

bool OrdinaryCargo::operator>(OrdinaryCargo const& c) const
{
	if (weight > c.weight)
		return true;
	else
		return false;
}

bool OrdinaryCargo::operator==(OrdinaryCargo const& c) const
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

bool UrgentCargo::is_delayed(){
	deadline -= 3600;
	if (deadline == 0) return true;
	else return false;
}

UrgentCargo::~UrgentCargo() {}
string UrgentCargo::check() const { return "urgent"; }
bool pred(OrdinaryCargo* cargo) { return (*cargo).get_erase_value(); }
