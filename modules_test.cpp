// air_travel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Flight.h"
#include "OrdinaryCargo.h"
#include "Airplane.h"
#include "Airport.h"
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
void Cargo_test() {
    // calling the default consructor
    time_t arrival_time = time(0) + (time_t)(3600), deadline = arrival_time + (time_t)(9 * 3600);
    UrgentCargo c(1, 25, "DME", "JFK", "ORY", arrival_time, deadline);
    assert(c.check() == "child");
    OrdinaryCargo* ptr = &c;
    assert(ptr->check() == "child");
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
    assert(c1.check() == "parent");
    assert((OrdinaryCargo)c > c1);
    assert(!((OrdinaryCargo)c < c1));
    assert(!((OrdinaryCargo)c == c1));
    assert(c1.get_erase_value() == false);
    c1.change_erase_value();
    assert(pred(c1) == true);
    int GlobalCargoCount = 0;
    time_t GlobalTime = time(0);
}
void Flight_test() {
    time_t departure_time = 0, arrival_time = 3600;
    Flight flight("SVO", "MMK", departure_time, arrival_time, 1);
    assert(flight.get_airplane_num() == 1);
    assert(flight.get_dep_ap() + flight.get_arr_ap() == "SVOMMK");
    assert(flight.get_dep_time() == 0);
    assert(flight.get_arr_time() == 3600);
}
void Airplane_test() {
    vector<OrdinaryCargo> ordinary_cargo;
    vector<UrgentCargo> urgent_cargo;
    for (int i = 1; i <= 10; ++i) {
        OrdinaryCargo cargo(i, (double)(i) * 10, "SVO", "MMK", "SVO", 0);
        UrgentCargo u_cargo(i + 1, (double)(i) * 10, "SVO", "MMK", "SVO", 0,
            24 * 3600);
        ordinary_cargo.push_back(cargo);
        urgent_cargo.push_back(u_cargo);
    }
    Airplane airbus(51, 5000, ordinary_cargo, urgent_cargo,
        "SVO", "MMK", "MMK", false, false);
    assert(airbus.get_num() == 51);
    assert(airbus.get_capacity() == 5000);
    assert(airbus.get_home_ap() + airbus.get_dest_ap() == "SVOMMK");
    assert(airbus.at_home());
    assert(!airbus.flight_status());
    airbus.in_flight_(1);
    assert(airbus.flight_status() && !airbus.at_home());
    OrdinaryCargo cargo;
    UrgentCargo u_cargo;
    assert((airbus.get_or_cargo_list()).size() +
        (airbus.get_ur_cargo_list()).size() == 20);
    airbus.add_cargo(cargo); airbus.add_cargo(u_cargo);
    assert((airbus.get_or_cargo_list()).size() +
        (airbus.get_ur_cargo_list()).size() == 22);
    assert(pred_for_plane(airbus));
}
void Airport_test() {
    time_t Global_Time = time(NULL);
    int Global_cargo_count = 1;
    vector<OrdinaryCargo> ordinary_cargo;
    vector<UrgentCargo> urgent_cargo;
    vector<Airplane> planes;
    vector<pair<string, int>> airports = { { "MMK", 2 }, { "OVB", 4 } };
    Airport SVO("SVO", ordinary_cargo, urgent_cargo, planes, airports);
    SVO.add_cargo(Global_cargo_count, Global_Time);
    Global_Time += (time_t)(3600);
    SVO.add_cargo(Global_cargo_count, Global_Time);
    assert(((size_t)Global_cargo_count-1) == (SVO.get_list_ordinary_cargo()).size() +
        (SVO.get_list_urgent_cargo()).size());
    Airplane airbus(51, 300, ordinary_cargo, urgent_cargo,
        "SVO", "MMK", "MMK", false, false);
    assert((airbus.get_or_cargo_list()).size() +
        (airbus.get_ur_cargo_list()).size() == 0);
    planes.push_back(airbus);
    SVO.set_list_airplanes(planes);
    SVO.cargo_to_plane();
    planes = SVO.get_list_airplanes();
    assert((planes[0].get_or_cargo_list()).size() +
        (planes[0].get_ur_cargo_list()).size() +
        (SVO.get_list_ordinary_cargo()).size() +
        (SVO.get_list_urgent_cargo()).size() == (size_t)Global_cargo_count - 1);
    cout << "Airbus in flight? " << planes[0].flight_status();
}
int main()
{
#define CARGO_DEBUG
#ifdef CARGO_DEBUG
    Cargo_test();
    Flight_test();
    Airplane_test();
    Airport_test();
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
