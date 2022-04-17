
from ctypes import *
import sys
print("c_void_p size")
print(sys.getsizeof(c_void_p))
cpp_dll = CDLL('C:/Users/PavelPodlesny/AppData/Local/Programs/Python/Python310/DLLs/Dll_air_transportation.dll')

arr_size = 100
c_arr_size = c_int(arr_size)
c_int_array_type = c_int*arr_size
c_str_type = c_char*110
large_c_str_type = c_char*200

GCC = c_int(1) #Global cargo count 
p_GCC = pointer(GCC)
#declaring function parameters
#CreateSchedule
cpp_dll.dll_CreateSchedule.argtypes = None
cpp_dll.dll_CreateSchedule.restype = c_void_p
#DeleteSchedule
cpp_dll.dll_DeleteSchedule.argtypes = [c_void_p]
cpp_dll.dll_DeleteSchedule.restype = None
#AddCargo
cpp_dll.dll_AddCargo.artypes = [c_void_p, POINTER(c_int)]
cpp_dll.dll_AddCargo.restype = None
#GetCountPlanesInAir
cpp_dll.dll_GetCountPlanesInAir.argtypes = [c_void_p]
cpp_dll.dll_GetCountPlanesInAir.restype = c_int
#SendingPlanes
cpp_dll.dll_SendingPlanes.argtypes = [c_void_p, c_char_p, POINTER(c_int), c_int]
cpp_dll.dll_SendingPlanes.restype = None
#WaitOneHour
cpp_dll.dll_WaitOneHour.argtypes = [c_void_p, c_char_p, POINTER(c_int), c_int]
cpp_dll.dll_WaitOneHour.restype = None
#Print
cpp_dll.dll_Print.argtypes = [c_void_p, c_char_p, POINTER(c_int), c_int]
cpp_dll.dll_Print.restype = None
#create new simple schedule
new_schedule = cpp_dll.dll_CreateSchedule()
print("pointer to schedule size")
print(sys.getsizeof(new_schedule))
#
total_num_ap = c_int(2) #total number of airplanes in this model
user_response = "next"
while user_response == "next":
    wait_time_ = 0
    wait_time_ = input("Please, enter waiting time in hours (integer).\nINPUT: ")
    wait_time = int(wait_time_)
    if not isinstance(wait_time, int):
        print("Incorrect input. Enter integer, not negative number.")
        continue
    elif wait_time <= 0:
        print("Waiting time equals zero or negative. No changes occured.")
        continue
    else:
        for iterator in range(wait_time):
            cpp_dll.dll_AddCargo(new_schedule, p_GCC) #add new cargo to both airports
            number_airplanes_in_air = c_int(0)
            zero = c_int(0)
            number_airplanes_in_air = cpp_dll.GetCountPlanesInAir(new_schedule)
            delayed_cargo = c_int_array_type() #array where number of delayed cargo will be stored
            if total_num_ap != number_airplanes_in_air:
                error_message_1 = c_str_type()# message about error 
                cpp_dll.dll_SendingPlanes(new_schedule, error_message_1, delayed_cargo, c_arr_size)
                ###need to end
                #if error_message[0] != b'\x00':
                    #print(error_message)
                if delayed_cargo[0] != zero:
                    iterator = 0
                    print("Sending planes|Delayed cargo numbers:", end = " ")
                    while delayed_cargo[iterator] != zero and iterator < 100:
                        print(delayed_cargo[iterator], ",", end = " ")
                        iterator += 1
                    print()
            for i in delayed_cargo:
                i = zero
            error_message_2 = c_str_type()
            cpp_dll.dll_WaitOneHour(new_schedule, error_message_2, delayed_cargo, c_arr_size)
            # add check of error message
            if delayed_cargo[0] != zero:
                iterator = 0
                print("WaitOneHour|Delayed cargo numbers:", end = " ")
                while delayed_cargo[iterator] != zero and iterator < 100:
                    print(delayed_cargo[iterator], ",", end = " ")
                    iterator += 1
                print()
            print("SCHEDULE:")
            text_schedule = large_c_str_type()
            error_message_3 = c_str_type()
            cpp_dll.dll_Print(new_schedule, error_message_3, text_schedule, c_int(200))
            print(text_schedule.value.decode('utf-8'))
        user_response = input("Enter 'next' to continue or 'end' to finish.\nINPUT: ")
        if user_response != "next" and user_response != "end":
            print("Incorrect input. Ending...")
            user_response = "end"
                               
###'''
cpp_dll.dll_DeleteSchedule(new_schedule)
print("Ok")
