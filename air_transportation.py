
from ctypes import *
import sys
import shutil
width = shutil.get_terminal_size().columns
separator = "=== ## ==="
#print("c_void_p size: ", sys.getsizeof(c_void_p))
cpp_dll = CDLL('C:/Users/PavelPodlesny/AppData/Local/Programs/Python/Python310/DLLs/Dll_air_transportation.dll')

arr_size = 100
c_arr_size = c_int(arr_size)
c_int_array_type = c_int*arr_size
c_str_type = c_char*110
large_c_str_type = c_char*200

GCC = c_int(1) #Global cargo count 
p_GCC = pointer(GCC)
#print("p_GCC size: ", sys.getsizeof(p_GCC))
#print("POINTER(c_int) size: ", sys.getsizeof(POINTER(c_int)))
#declaring function parameters
#CreateSchedule
cpp_dll.dll_CreateSchedule.argtypes = None
cpp_dll.dll_CreateSchedule.restype = c_void_p
#DeleteSchedule
cpp_dll.dll_DeleteSchedule.argtypes = [c_void_p]
cpp_dll.dll_DeleteSchedule.restype = None
#AddCargo
cpp_dll.dll_AddCargo.argtypes = [c_void_p, POINTER(c_int)]
cpp_dll.dll_AddCargo.restype = c_int
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
cpp_dll.dll_Print.argtypes = [c_void_p, c_char_p, c_char_p, c_int]
cpp_dll.dll_Print.restype = None
#PrintTime
cpp_dll.dll_PrintTime.argtypes = [c_void_p, c_char_p]
cpp_dll.dll_PrintTime.restype = None
#
#create new simple schedule
new_schedule = cpp_dll.dll_CreateSchedule()
#print("pointer to schedule size", sys.getsizeof(new_schedule))
#
title1 = "A simple model of air transportation"
title2 = "by Pavel Podlesny"
title3 = "MIPT, 2022"
print(title1.center(width))
print(title2.center(width))
print(title3.center(width))
total_num_ap = c_int(6) #total number of airplanes in this model
user_response = "next"
while user_response == "next":
    try:
        wait_time = int(input("Please, enter waiting time in hours (integer).\nINPUT: "))
        print("\n", separator.center(width))
        if wait_time <= 0:
            raise Exception("Waiting time equals zero or negative. No changes occured.")
        else:###arrays where number of delayed cargo will be stored
            delayed_cargo_1 = c_int_array_type()
            delayed_cargo_2 = c_int_array_type()
            i = 0
            while i < 100:
                delayed_cargo_1[i] = 0
                delayed_cargo_2[i] = 0
                i += 1
            ##  start for  
            for iterator in range(wait_time):
                error_flag = cpp_dll.dll_AddCargo(new_schedule, p_GCC) #add new cargo to both airports
                if(error_flag == -1):
                    print("DLL_error|AddCargo|invalid constructor's parameters")
                number_airplanes_in_air = c_int(0)
                number_airplanes_in_air = cpp_dll.dll_GetCountPlanesInAir(new_schedule)
                if total_num_ap != number_airplanes_in_air:
                    error_message_1 = create_string_buffer(109)# message about error
                    cpp_dll.dll_SendingPlanes(new_schedule, error_message_1, delayed_cargo_1, c_arr_size)
                    ###check error message
                    if error_message_1[0] != b'\x00':
                        print(error_message_1.value.decode('utf-8'))
                error_message_2 = create_string_buffer(109)
                cpp_dll.dll_WaitOneHour(new_schedule, error_message_2, delayed_cargo_2, c_arr_size)
                # add check of error message
                if error_message_2[0] != b'\x00':
                    print(error_message_2.value.decode('utf-8'))
                '''if delayed_cargo[0] != 0:
                    iterator = 0
                    print("WaitOneHour|Delayed cargo numbers:", end = " ")
                    while iterator < 100 and delayed_cargo[iterator] != 0:
                        print(delayed_cargo[iterator], " ", end = " ")
                        iterator += 1
                    print()'''
            ## end for
            ##
            ## global cargo count
            print("Global cargo count: ", p_GCC.contents) #for checking 
            print("DATA and TIME:", end = " ")
            text_time = create_string_buffer(29)
            cpp_dll.dll_PrintTime(new_schedule, text_time)
            print(text_time.value.decode('utf-8'), end = "")
            if delayed_cargo_1[0] != 0:
                iterator = 0
                print("Cargo delayed in transit:", end = " ")
                while iterator < 100 and delayed_cargo_1[iterator] != 0:
                    print(delayed_cargo_1[iterator], " ", end = " ")
                    iterator += 1
                print()
            if delayed_cargo_2[0] != 0:
                iterator = 0
                print("Cargo delayed in airports:", end = " ")
                while iterator < 100 and delayed_cargo_2[iterator] != 0:
                    print(delayed_cargo_2[iterator], " ", end = " ")
                    iterator += 1
                print()
            title4 = "SCHEDULE:"
            print(title4.center(width))
            str_ = "#"
            print(str_.rjust(2), end = "")
            str_ = "Departure airport"
            print(str_.center(21), end = "")
            str_ = "Arrival airport"
            print(str_.center(17), end = "")
            str_ = "Airplane number"
            print(str_.center(17), end = "")
            str_ = "Departure"
            print(str_.center(26), end = "")
            str_ = "Arrival"
            print(str_.center(28))
            text_schedule = create_string_buffer(499)
            #print(type(text_schedule))
            error_message_3 = create_string_buffer(109)
            cpp_dll.dll_Print(new_schedule, error_message_3, text_schedule, c_int(500))
            if error_message_3[0] != b'x00':
                print(error_message_3.value.decode('utf-8'))
            python_schedule = text_schedule.value.decode('utf_8')
            schedule_records = python_schedule.split('|')
            i = 0
            while i < len(schedule_records)-1:
                schedule_string = schedule_records[i].split(';')
                print(schedule_string[0].rjust(2), end = "")
                print(schedule_string[1].center(21), end = "")
                print(schedule_string[2].center(17), end = "")
                print(schedule_string[3].center(17), end = "")
                print(schedule_string[4].center(26), end = "")
                print(schedule_string[5].center(28))
                i += 1
            print("\n", separator.center(width))
        #print(python_schedule)
        #print(text_schedule.value.decode('utf-8'))#'''
    except  ValueError as error_1:
        print("Incorrect input: ", error_1, "\nEnter integer, not negative number")
        continue
    except Exception as error_2:
        print(error_2)
        continue
    try:
        user_response = input("\nEnter 'next' to continue or 'end' to finish.\nINPUT: ")
        if user_response != "next" and user_response != "end":
            raise Exception("Incorrect input. Ending...")
    except Exception as error_3:
        print(error_3)
        user_response = "end"
                               
###'''
cpp_dll.dll_DeleteSchedule(new_schedule)
print("Successful completion")
