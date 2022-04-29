#ifndef SCHEDULE
#define SCHEDULE

/*#ifdef DLL_AIR_TRANSPORTATION_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif*/

#include "Airport.h"
#include "Flight.h"
#define MAX_SIZE 200
#define DllExport __declspec(dllexport)
class Schedule
{
private:
	time_t Global_time;
	vector<Airport> airports;
	vector<Flight> schedule;
	vector<pair<Airplane, time_t>> planes_in_air; //time_t == time in flight
public:
	Schedule(time_t Global_time, vector<Airport>& airports, vector<Flight>& schedule, vector<pair<Airplane, time_t>>& planes_in_air);
	void add_flight(string dep_ap, string arr_ap, time_t dep_time, time_t arr_time,
		int plane_num);
	void del_flight(int plane_num);
	void add_plane(Airplane& plane, time_t time_in_flight);
	int add_cargo(int* global_cargo_count); // in final version change int to void 
	void sending_planes(char* error_line, int* delayed_cargo, int size);
	void landing_plane(Airplane& plane);
	void wait_one_hour(char* error_message, int* delayed_cargo, int size);
	void print(char* error_message, char* text_schedule, int size);
	vector<Airport> const& get_airports_list();
	vector<Flight> const& get_flights_list();
	vector<pair<Airplane, time_t>> const& get_planes_in_air_list();
	size_t get_global_time();
	size_t get_size_planes_in_air_list();
};
bool compare(OrdinaryCargo* i, OrdinaryCargo* j);
extern "C" {
	__declspec(dllexport) int dll_AddCargo(Schedule* schedule, int* glb);
	__declspec(dllexport) void dll_SendingPlanes(Schedule* schedule, char* error_message, int* delayed_cargo, int size);
	__declspec(dllexport) void dll_WaitOneHour(Schedule* schedule, char* error_message, int* delayed_cargo, int size);
	__declspec(dllexport) void dll_Print(Schedule* schedule, char* error_message, char* text_schedule, int size);
	__declspec(dllexport) void dll_DeleteSchedule(Schedule* schedule);
	__declspec(dllexport) Schedule* dll_CreateSchedule();
	__declspec(dllexport) void dll_PrintTime(Schedule* schedule, char* text_time);
	__declspec(dllexport) int dll_GetCountPlanesInAir(Schedule* schedule);
}
#endif

