#ifndef  ORDINARY_CARGO
#define ORDINARY_CARGO
#include "MainHeader.h"
//bool check_time(string const& ap);

class OrdinaryCargo
{
private:
	int num;
	double weight;//kg
	string dep_ap, arr_ap, curr_ap; // departure airport, arrival -/-, current -/-
	time_t time_;// data and time when cargo is arrived to airport
	bool erase; // i need this value to know whether a object will be deleted
public:
	// constructor and destructor
	OrdinaryCargo(int num = 0, double weight = 0,
		string dep_ap = "", string arr_ap = "", string curr_ap = "",
		time_t time_ = 0, bool erase = false);
	virtual ~OrdinaryCargo();
	// methods of getting of the fields
	int get_num() const;
	double get_weight() const;
	string  get_dep_ap() const;
	string  get_arr_ap() const;
	string  get_curr_ap() const;
	time_t get_time() const;
	bool get_erase_value() const;
	// methods of changing of the fields
	void change_curr_ap(string &ap);
	void change_erase_value();
	virtual string check() const; // parent or child class?
	//virtual bool is_delayed();
	//virtual time_t get_deadline() const;
	bool operator< (OrdinaryCargo const& c) const;
	bool operator> (OrdinaryCargo const& c) const;
	bool operator== (OrdinaryCargo const& c) const;

};
class UrgentCargo : public OrdinaryCargo {
private:
	time_t deadline;
public:
	UrgentCargo( int num = 0, double weight = 0,
		string dep_ap = "", string arr_ap = "", string curr_ap = "",
		time_t time_ = 0, time_t deadline = 0, bool erase = false);
	~UrgentCargo();
	bool is_delayed();
	time_t get_deadline() const;
	string check() const;
};
bool pred(OrdinaryCargo* cargo);
#endif

