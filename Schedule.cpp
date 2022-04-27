#include "Schedule.h"
#define small_char_buff_size  110
#define large_char_buff_size 200

//#define TEST
#ifdef TEST
void print_test() {
	int glb = 1;
	Schedule* new_schedule = dll_CreateSchedule();
	for (int i = 0; i < 5; ++i)
		dll_AddCargo(new_schedule, &glb);
	char error_message[100];
	int delayed_cargo[100];
	for (int i = 0; i < 100; i++)
		delayed_cargo[i] = 0;
	dll_SendingPlanes(new_schedule, error_message, delayed_cargo, 100);
	char text_schedule[200];
	for (int i = 0; i < 199; ++i)
		text_schedule[i] = '0';
	text_schedule[199] = '\0';
	cout << "strlen: " << strlen(text_schedule) << " sizeof: " << sizeof(text_schedule) << endl;
	const char* str = "Hello"; //6 char
	strcpy_s(text_schedule, _countof(text_schedule), "\0");
	//strcat_s(text_schedule, _countof(text_schedule), ", world!");
	//printf("text_schedule <- 'Hello, world!': %s\n", text_schedule);
	cout << "strlen: " << strlen(text_schedule) << " sizeof: " << sizeof(text_schedule) << endl;
	dll_Print(new_schedule, error_message, text_schedule, 200);
	printf("output:\n%s", text_schedule);
	dll_DeleteSchedule(new_schedule);
}
#endif
Schedule::Schedule(time_t Global_time, vector<Airport>& airports, vector<Flight>& schedule, vector<pair<Airplane,
	time_t>>& planes_in_air)
{
	this->Global_time = Global_time;
	this->schedule = schedule;
	this->planes_in_air = planes_in_air;
	this->airports = airports;
}

vector<Airport> const& Schedule::get_airports_list() { return airports; }

vector<Flight> const& Schedule::get_flights_list() { return schedule; }

vector<pair<Airplane, time_t>> const& Schedule::get_planes_in_air_list() { return planes_in_air; }

void Schedule::del_flight(int plane_num)
{
	auto i = schedule.begin(), end = schedule.end();
	while (i != end && plane_num != (*i).get_airplane_num()) ++i;
	if (i == end) std::cerr << "Schedule|del_flight|plane isn't found" << endl;
	else schedule.erase(i);
}

void Schedule::add_flight(string dep_ap, string arr_ap, time_t dep_time, time_t arr_time, int plane_num)
{
	Flight flight(dep_ap, arr_ap, dep_time, arr_time, plane_num);
	schedule.push_back(flight);
}

void Schedule::add_plane(Airplane& plane, time_t time_in_flight)
{
	pair<Airplane, time_t> air_travel = {plane, time_in_flight};
	planes_in_air.push_back(air_travel);
}

void Schedule::add_cargo(int* global_cargo_count){
	for (auto i = airports.begin(); i != airports.end(); ++i) {
		(*i).add_cargo(global_cargo_count, Global_time);
	}
}

void Schedule::landing_plane(Airplane& plane){
	plane.change_flight_status(0);
	for (auto j = plane.get_cargo_list().begin(); j != plane.get_cargo_list().end(); ++j) {
		delete (*j);
	}
	plane.unload_cargo();
	auto i = airports.begin(), end = airports.end();
	while (i != end && plane.get_dest_ap() != (*i).get_name()) ++i;
	if (i == end) std::cerr << "Schedule|landing|airpirt isn't found";
	else {
		if (plane.get_home_ap() == plane.get_dest_ap()) plane.change_dest_ap(plane.get_other_ap());
		else plane.change_dest_ap(plane.get_home_ap());
		(*i).add_airplane(plane);
		del_flight(plane.get_num());
	}
}

void Schedule::wait_one_hour(char* error_message, int* delayed_cargo, int size){
	// set delayed_cargo array to first zero position 
	bool overload = 0;
	int occupied_size = 0;
	int j = 0;
	while (j < size && delayed_cargo[j] != 0) { ++j; }
	if (j == size) {
		strcpy_s(error_message, small_char_buff_size, "Schedule|wait_one_hour|buffer is overload");
		occupied_size = size;  overload = 1;
	}
	else { delayed_cargo += j; occupied_size += j; }
	//
	Global_time += 3600;
	//landing planes
	auto i = planes_in_air.begin(), end = planes_in_air.end();
	for (i; i != end; ++i) {
		(*i).second -= (time_t)(3600);
		if ((*i).second <= 0) landing_plane((*i).first);
	}
	planes_in_air.erase(std::remove_if(planes_in_air.begin(), planes_in_air.end(), pred_for_plane_and_time), planes_in_air.end());
	//urgent_cargo.erase(std::remove_if(urgent_cargo.begin(), urgent_cargo.end(), pred), urgent_cargo.end());
	for (auto i = airports.begin(); i != airports.end(); ++i) {
		for (auto j = (*i).get_cargo_list().begin(); j != (*i).get_cargo_list().end(); ++j) {
			if ((*j)->check() == "urgent")
				if ( ((UrgentCargo*)(*j))->is_delayed() ) {
					if (occupied_size < size) {
						(*delayed_cargo) = (*j)->get_num();
						delayed_cargo++;
						occupied_size++;
					}
					else{if (!overload) { overload = 1; strcpy_s(error_message, small_char_buff_size, "Schedule|wait_one_hour|buffer is overload"); }}
				}
		}
	}
	
}

void Schedule::print(char* error_message, char* text_schedule, int size) {
	//lenght_of_buffer = 132; (65*2 = data) + '|' + '\0'
	bool overload = false;
	int actual_size = size;
	int count = 1;
	/*cout << setw(9) << left << "Flight #";
	cout << setw(19) << "Departure airport";
	cout << setw(15) << right << "Arrival airport" << " ";
	cout << setw(5) << " " << "Departure time" << setw(5) << " ";
	cout << "	";
	cout << setw(6) << " " << "Arrival time" << setw(6) << " ";
	cout << "	";
	cout << setw(12) << "Plane number" << endl;*/
	auto i = schedule.begin();
	char buf[26];
	while( !overload && (i != schedule.end()) ){
		string cpp_string_output = std::to_string(count) + ";";
		string cpp_string = (*i).get_dep_ap() + ";";
		cpp_string_output += cpp_string;
		cpp_string = (*i).get_arr_ap() + ";";
		cpp_string_output += cpp_string;
		cpp_string = std::to_string((*i).get_airplane_num()) + ";";
		cpp_string_output += cpp_string;
		const char* c_string = (cpp_string_output.c_str());
		strcat_s(text_schedule, large_char_buff_size, c_string);
		time_t time_ = (*i).get_dep_time();
		ctime_s(buf, sizeof(buf), &time_); buf[24] = ';';
		strcat_s(text_schedule, large_char_buff_size, buf);
		time_ = (*i).get_arr_time();
		ctime_s(buf, sizeof(buf), &time_); buf[24] = ' ';
		strcat_s(text_schedule, large_char_buff_size, buf);
		strcat_s(text_schedule, large_char_buff_size, "|");
		count++;
		++i;
		actual_size -= 66;
		if (actual_size < 66) { overload = true; strcpy_s(error_message, small_char_buff_size, "Schedule|print|buffer is overload"); }
	}
	//text_schedule[size - 1] = '\0';
}

size_t Schedule::get_global_time() { return (size_t)Global_time; }
size_t Schedule::get_size_planes_in_air_list() { return planes_in_air.size(); }

void Schedule::sending_planes(char* error_line, int* delayed_cargo, int size) {
	// set delayed_cargo array to first zero position 
	bool overload = 0;
	int occupied_size = 0;
	int k = 0;
	while (k < size && delayed_cargo[k] != 0) { ++k; }
	if (k == size) {
		strcpy_s(error_line, small_char_buff_size, "Schedule|sending_planes|buffer is overload");
		occupied_size = size;  overload = 1;
	}
	else { delayed_cargo += k; occupied_size += k; }
	//
	time_t global_time = this->Global_time;
	for(auto airport_ = airports.begin(); airport_!=airports.end(); ++airport_){
	vector <Airplane> airplanes = (*airport_).get_airplanes_list();
	vector <OrdinaryCargo*> cargo = (*airport_).get_cargo_list();
	for (auto i = airplanes.begin(); i != airplanes.end(); ++i) {
		double free_payload = ((*i).get_capacity()), initial_payload = free_payload;
		string destination_airport = (*i).get_dest_ap();
		bool overflow = false;
		// how long is travel
		time_t time_in_flight = 0;
		vector<pair<string, int>> other_airports = (*airport_).get_other_airports_list();
		auto j = other_airports.begin(), j_end = other_airports.end();
		while (j != j_end && destination_airport != (*j).first) { ++j; }
		if (j == j_end) {
			const char error_message[] = "Schedule|sending_planes|destination airport isn't found";
			strcpy_s(error_line, small_char_buff_size, error_message);
		}
		else time_in_flight = (time_t)((*j).second * 3600);
		// DEBUG
		//cout << "DEBUG|time_in_flight value:" << time_in_flight << endl;
		// DEBUG
		// insert
		sort(cargo.begin(), cargo.end(), compare); //!!!
		auto c = cargo.begin(), c_end = cargo.end();
		while (c != c_end && !overflow) { // cycle by urgent cargo
			if ((*c)->check() == "urgent" && (*c)->get_arr_ap() == destination_airport) {
				if ((*i).add_cargo(free_payload, (*c)->get_weight(), *c)) {
					// DEBUG
					//cout << "DEBUG|deadline_time value:" << ((UrgentCargo*)(*c))->get_deadline() << endl;
					// DEBUG
					if (time_in_flight > ((UrgentCargo*)(*c))->get_deadline()) {

						if(occupied_size < size){
							(*delayed_cargo) = (*c)->get_num();
							delayed_cargo++;
							occupied_size++;
						}
						else { if (!overload) { overload = 1; strcat_s(error_line, small_char_buff_size, "\nSchedule|sending_planes|buffer is overload"); } }
					}
					(*c)->change_erase_value();}
				else overflow = true;
			}
			++c;
		}
		//delayed_cargo -= actual_size;
		if (free_payload <= (0.25 * initial_payload)) {
			(*i).change_flight_status(1);
			//start flight
			add_flight((*airport_).get_name(), destination_airport,
					global_time, global_time + time_in_flight, (*i).get_num());
			add_plane((*i), time_in_flight);
			//start flight
		}
		else {
			overflow = false;
			c = cargo.begin(); c_end = cargo.end();
			while (c != c_end && !overflow) {
				if ((*c)->check() == "ordinary" && (*c)->get_arr_ap() == destination_airport) {
					if ((*i).add_cargo(free_payload, (*c)->get_weight(), *c)) { (*c)->change_erase_value(); }
					else overflow = true;
				}
				++c;
			}
			if (free_payload <= (0.25 * initial_payload)) {
				(*i).change_flight_status(1);
				add_flight((*airport_).get_name(), destination_airport,
						global_time, global_time + time_in_flight, (*i).get_num());
				add_plane((*i), time_in_flight);
				//start flight
			}
		}
		cargo.erase(std::remove_if(cargo.begin(), cargo.end(), pred), cargo.end()); //!

	}
	airplanes.erase(std::remove_if(airplanes.begin(), airplanes.end(), pred_for_plane), airplanes.end());
	//if the airplane took off, move it to "plane_in_flight" list
	(*airport_).set_airplanes_list(airplanes);
	(*airport_).set_cargo_list(cargo);
	}
}

bool compare(OrdinaryCargo* i, OrdinaryCargo* j) { return (i->operator<(*j)); }

extern "C" {
	 void dll_AddCargo(Schedule* schedule, int* glb) { schedule->add_cargo(glb); }
	 void dll_SendingPlanes(Schedule* schedule, char* error_message, int* delayed_cargo, int size){
		schedule->sending_planes(error_message, delayed_cargo, size); }
	 void dll_WaitOneHour(Schedule* schedule, char* error_message, int* delayed_cargo, int size) { schedule->wait_one_hour(error_message, delayed_cargo, size); }
	 void dll_Print(Schedule* schedule, char* error_message, char* text_schedule, int size) { schedule->print(error_message, text_schedule, size); } // NEED CHANGE!!!
	 void dll_DeleteSchedule(Schedule* schedule) { delete schedule; };
	 Schedule* dll_CreateSchedule() {
		vector<OrdinaryCargo*> cargo;
		//create two new airports
		Airplane airbus_one(1, 300, cargo, "SVO", "MMK", "MMK", false);
		vector<Airplane> planes{ airbus_one };
		vector<pair<string, int>> airports{ { "MMK", 5 } };
		Airport SVO("SVO", cargo, planes, airports);
		planes.clear(); airports.clear();
		//
		Airplane airbus_two(2, 400, cargo, "MMK", "SVO", "SVO", false);
		planes.push_back(airbus_two); airports.push_back({ "SVO", 5 });
		Airport MMK("MMK", cargo, planes, airports);
		// create schedule
		vector<Airport> AirPorts{ SVO, MMK }; vector<Flight> flight_list;
		vector<pair<Airplane, time_t>> planes_in_air;
		return new Schedule(time(NULL), AirPorts, flight_list, planes_in_air);
	}
	 void dll_PrintTime(Schedule* schedule, char* text_time) {
		 time_t time_ = (schedule->get_global_time());
		 ctime_s(text_time, 30, &time_);
	 }
	 int dll_GetCountPlanesInAir(Schedule* schedule) { return (int)(schedule->get_size_planes_in_air_list()); }
}