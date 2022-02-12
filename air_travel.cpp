// air_travel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "OrdinaryCargo.h"
#include <iostream>
void print_class(OrdinaryCargo const& cargo) {
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
    std::cout << num << " " << weight << " " << str << std::endl;
}
void OrdinaryCargo_test() {
    
    typedef OrdinaryCargo Cargo;
    // вызов конструктора по умолчанию
    Cargo c_0;
    print_class(c_0);
    //проверка change_curr_ap
    string new_curr_ap = "OVB";
    c_0.change_curr_ap(new_curr_ap);
    print_class(c_0);

    new_curr_ap = "ovb";
    c_0.change_curr_ap(new_curr_ap);
    print_class(c_0);
    // вызов конструктора с правильными параметрами
    Cargo c_1(1, 25, "DME", "JFK", "ORY", "13:45");
    print_class(c_1);
    // вызов конструктора с неправильными параметрами
    Cargo c_2(-3, 112, "dME", "J1K", "ORY_", "00:00");
    print_class(c_2);
}

int main()
{
#define DEBUG
#ifdef DEBUG
    OrdinaryCargo_test();
#endif // DEBUG

    
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
