#ifndef  ORDINARY_CARGO
#define ORDINARY_CARGO
#include "MainHeader.h"
//bool check_time(string const& ap);

class OrdinaryCargo
{
protected:
	int num;
	double weight;
	string dep_ap, arr_ap, curr_ap; // departure airport, arrival -/-, current -/-
	time_t time_;
	bool erase;// data and time when cargo is arrived to airport
public:
	// constructor and destructor
	OrdinaryCargo(int num = 0, double weight = 0,
		string dep_ap = "", string arr_ap = "", string curr_ap = "",
		time_t time_ = 0, bool erase = false);
	~OrdinaryCargo();
	// methods of getting of the fields
	int get_num() const;
	double get_weight() const;
	string  get_dep_ap() const;
	string  get_arr_ap() const;
	string  get_curr_ap() const;
	time_t get_time() const;
	bool get_erase() const;
	// methods of changing of the fields
	void change_curr_ap(string &ap);
	void erase_();
	// metod for print 
	//void print_class();
	//
	bool operator< (OrdinaryCargo const& c);
	bool operator> (OrdinaryCargo const& c);
	bool operator== (OrdinaryCargo const& c);

};
class UrgentCargo : public OrdinaryCargo {
private:
	time_t deadline;
public:
	UrgentCargo( int num = 0, double weight = 20.0,
		string dep_ap = "SVO", string arr_ap = "MMK", string curr_ap = "SVO",
		time_t time_ = time(0), time_t deadline = (time(0) + (time_t)(10 * 3600)), bool erase = false);
	time_t get_deadline() const;
};
bool pred(OrdinaryCargo& cargo);
#endif

