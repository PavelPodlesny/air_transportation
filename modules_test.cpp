// air_travel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Flight.h"
#include "OrdinaryCargo.h"
#include "Airplane.h"
#include "Airport.h"
#include "Schedule.h"
#include <cassert>
/*void print_class(OrdinaryCargo const& cargo) {
    int num;
    double weight;
    string dep_ap, arr_ap, curr_ap, time_;
    num = cargo.get_num();
    weight = cargo.get_weight();
    dep_ap = cargo.get_dep_ap();
    arr_ap = cargo.get_arr_ap();
    curr_ap = cargo.get_curr_ap();
    time_ = cargo.get_time();
    string str = dep_ap + " " + curr_ap + " " + arr_ap + " " + time_;
    cout << num << " " << weight << " " << str << endl;
}*/
void Test() {
    OrdinaryCargo ordinary;
    UrgentCargo urgent;
    OrdinaryCargo* ref = &ordinary;
    cout << (*ref).check() << endl;
    ref = &urgent;
    cout << (*ref).check();
}

void count_planes_on_land_and_in_air(Schedule& schedule, time_t* Global_time) {
    char buf[100];
    ctime_s(buf, sizeof(buf), Global_time);
    cout << "Time: " << buf;
    size_t count_planes_on_land = 0, count_planes_in_air = 0;
    vector<Airport> airports_list = schedule.get_airports_list();
    for (auto i = airports_list.begin(); i != airports_list.end(); ++i) {
        count_planes_on_land += (*i).get_airplanes_list().size();
    }
    count_planes_in_air = schedule.get_planes_in_air_list().size();
    cout << "Planes on land: " << count_planes_on_land << endl;
    cout << "Planes in air: " << count_planes_in_air << endl;
    cout << "Record in schedule: " << schedule.get_flights_list().size() << endl;
    cout << endl;
}
void count_cargo_on_land_and_in_air(Schedule& schedule, int Global_cargo_count) {
    size_t cargo_count_on_land = 0, cargo_count_in_air = 0;
    vector<Airport> airports_list = schedule.get_airports_list();
    for (auto i = airports_list.begin(); i != airports_list.end(); ++i) {
        cargo_count_on_land += (*i).get_cargo_list().size();
        for (auto j = (*i).get_airplanes_list().begin(); j != (*i).get_airplanes_list().end(); ++j) {
            cargo_count_on_land += (*j).get_cargo_list().size();
        }
    }
    vector<pair<Airplane, time_t>> planes_in_air = schedule.get_planes_in_air_list();
    for (auto i = planes_in_air.begin(); i != planes_in_air.end(); ++i) {
        cargo_count_in_air += (*i).first.get_cargo_list().size();
    }
    cout << "Cargo on land: " << cargo_count_on_land << endl;
    cout << "Cargo in air: " << cargo_count_in_air << endl;
    cout << "Global cargo count: " << Global_cargo_count - 1 << endl;
    cout << endl;
}
void Cargo_test() {
    // calling the default consructor
    time_t arrival_time = time(0) + (time_t)(3600), deadline = arrival_time + (time_t)(9 * 3600);
    UrgentCargo c(1, 25, "DME", "JFK", "ORY", arrival_time, deadline);
    assert(c.check() == "urgent");
    OrdinaryCargo* ptr = &c;
    assert(ptr->check() == "urgent");
    assert(c.get_num() == 1);
    assert(c.get_weight() == 25);
    string str = c.get_dep_ap() + c.get_arr_ap() + c.get_curr_ap();
    assert(str == "DMEJFKORY");
    assert(c.get_time() == arrival_time);
    assert(c.get_deadline() == deadline);
    string new_curr_ap = "DME"; c.change_curr_ap(new_curr_ap);
    assert((str = c.get_curr_ap()) == "DME");
    new_curr_ap = "ovb"; c.change_curr_ap(new_curr_ap);
    OrdinaryCargo c1(2, 10, "DME", "JFK", "DME", arrival_time, false);
    assert(c1.check() == "ordinary");
    assert((OrdinaryCargo)c > c1);
    assert(!((OrdinaryCargo)c < c1));
    assert(!((OrdinaryCargo)c == c1));
    assert(c1.get_erase_value() == false);
    c1.change_erase_value();
    assert(pred(&c1) == true);
    int GlobalCargoCount = 0;
    time_t GlobalTime = time(0);
    cout << "Cargo_test: OK" << endl;
}
void Flight_test() {
    time_t departure_time = 0, arrival_time = 3600;
    Flight flight("SVO", "MMK", departure_time, arrival_time, 1);
    assert(flight.get_airplane_num() == 1);
    assert(flight.get_dep_ap() + flight.get_arr_ap() == "SVOMMK");
    assert(flight.get_dep_time() == 0);
    assert(flight.get_arr_time() == 3600);
    cout << "Flight_test: OK" << endl;
}
void Airplane_test() {
    vector<OrdinaryCargo*> arr_cargo;
    for (int i = 1; i <= 10; ++i) {
        OrdinaryCargo* cargo = new OrdinaryCargo(i, (double)(i) * 10, "SVO", "MMK", "SVO", 0);
        UrgentCargo* u_cargo = new UrgentCargo(i + 1, (double)(i) * 10, "SVO", "MMK", "SVO", 0,
            24 * 3600);
        arr_cargo.push_back(cargo);
        arr_cargo.push_back(u_cargo);
    }
    Airplane airbus(51, 5000, arr_cargo,"SVO", "MMK", "MMK", false);
    assert(airbus.get_num() == 51);
    assert(airbus.get_capacity() == 5000);
    assert(airbus.get_home_ap() + airbus.get_dest_ap() == "SVOMMK");
    assert(!airbus.get_flight_status());
    airbus.change_flight_status(1);
    assert(airbus.get_flight_status());
    OrdinaryCargo* cargo = new OrdinaryCargo;
    double free_payload = airbus.get_capacity();
    assert(airbus.add_cargo(free_payload, cargo->get_weight(), cargo));
    assert(free_payload == airbus.get_capacity() - cargo->get_weight());
    assert((airbus.get_cargo_list()).size() == 21);
    for (auto i = airbus.get_cargo_list().begin(); i != airbus.get_cargo_list().end(); ++i) { delete (*i); }
    airbus.unload_cargo();
    assert((airbus.get_cargo_list()).size() == 0);
    assert(airbus.flight_direction() == "direct");
    assert(pred_for_plane(airbus));
    cout << "Airplane_test: OK" << endl;
}
void Airport_test() {
    time_t Global_Time = time(NULL);
    int Global_cargo_count = 1;
    vector<OrdinaryCargo*> arr_cargo;
    vector<Airplane> planes;
    vector<pair<string, int>> airports = { { "MMK", 2 }, { "OVB", 4 } };
    Airport SVO("SVO", arr_cargo, planes, airports);
    SVO.add_cargo(Global_cargo_count, Global_Time);
    Global_Time += (time_t)(3600);
    SVO.add_cargo(Global_cargo_count, Global_Time);
    assert((size_t)(Global_cargo_count-1) == (SVO.get_cargo_list()).size());
    Airplane airbus(51, 300, arr_cargo,"SVO", "MMK", "MMK", false);
    assert((airbus.get_cargo_list()).size() == 0);
    SVO.add_airplane(airbus);
    assert(SVO.get_airplanes_list().size()==1);
    for (auto i = SVO.get_cargo_list().begin(); i != SVO.get_cargo_list().end(); ++i) delete (*i);
    cout << "Airport_test: OK" << endl << endl;
}
void Schedule_test() {
    cout << "'Schedule test' is starting..." << endl;
    time_t Global_Time = time(NULL);
    int Global_cargo_count = 1;
    vector<OrdinaryCargo*> cargo;
    //create two new airports
    Airplane airbus_1(1, 300, cargo, "SVO", "MMK", "MMK", false);
    vector<Airplane> planes{airbus_1};
    vector<pair<string, int>> airports{{ "MMK", 5 }};
    Airport SVO("SVO", cargo, planes, airports);
    planes.clear(); airports.clear();
    //
    Airplane airbus_2(2, 400, cargo, "MMK", "SVO", "SVO", false);
    planes.push_back(airbus_2); airports.push_back({"SVO", 5});
    Airport MMK("MMK", cargo, planes, airports);
    // crtate schedule
    vector<Airport> AirPorts{ SVO, MMK }; vector<Flight>flight_list;
    vector<pair<Airplane, time_t>>planes_in_air;
    Schedule simple_schedule(AirPorts, flight_list, planes_in_air);
    simple_schedule.add_cargo(Global_cargo_count, Global_Time);
    Global_Time += (time_t)3600;
    simple_schedule.add_cargo(Global_cargo_count, Global_Time);
    cout << "|Before departure|" << endl;
    count_cargo_on_land_and_in_air(simple_schedule, Global_cargo_count);
    cout << "|Starting departure|" << endl;
    simple_schedule.sending_planes(Global_Time); // send planes to travel
    count_cargo_on_land_and_in_air(simple_schedule, Global_cargo_count);
    count_planes_on_land_and_in_air(simple_schedule, &Global_Time);
    // program is working correct till this row 
    // check number of cargo on land and in air
    cout << "|Schedule|" << endl;
    simple_schedule.print();
    cout << "Wait for 4 hours" << endl;
    for (int i = 0; i < 4; ++i) {
        Global_Time += 3600; simple_schedule.add_cargo(Global_cargo_count, Global_Time);
        simple_schedule.wait_one_hour();
    }
    Global_Time += 3600; simple_schedule.add_cargo(Global_cargo_count, Global_Time);
    cout << "|After 5 hours, before landing|" << endl;
    count_cargo_on_land_and_in_air(simple_schedule, Global_cargo_count);
    count_planes_on_land_and_in_air(simple_schedule, &Global_Time);
    simple_schedule.wait_one_hour();
    cout << "|After landing|" << endl;
    count_cargo_on_land_and_in_air(simple_schedule, Global_cargo_count);
    count_planes_on_land_and_in_air(simple_schedule, &Global_Time);
    for (auto j = simple_schedule.get_airports_list().begin(); j != simple_schedule.get_airports_list().end(); ++j){
        for (auto i = (*j).get_cargo_list().begin(); i != (*j).get_cargo_list().end(); ++i) delete (*i);
    }
}
int main()
{
//#define TEST
#define DEBUG
#ifdef DEBUG
    Cargo_test();
    Flight_test();
    Airplane_test();
    Airport_test();
    Schedule_test();
#endif
#ifdef TEST
    Test();
#endif

    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
