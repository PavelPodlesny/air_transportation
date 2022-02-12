#pragma once
#include <string>
using std::string;

bool check_ap(string const& ap);

class OrdinaryCargo
{
private:
	int num;
	double weight;
	string dep_ap, arr_ap, curr_ap;
	string time; // уточнить, что означает поле
public:
	// конструктор и деструктор
	OrdinaryCargo(int num = 0, double weight = 20.0,
		string dep_ap = "SVO", string arr_ap = "MMK", string curr_ap = "SVO",
		string time = "20:00");
	~OrdinaryCargo();
	// методы получения полей
	int get_num() const;
	double get_weight() const;
	string const& get_dep_ap() const;
	string const& get_arr_ap() const;
	string const& get_curr_ap() const;
	string const& get_time() const;
	// методы изменения полей
	void change_curr_ap(string &ap);
};

