import ctypes
my_lib = ctypes.CDLL("C:/Users/PavelPodlesny/AppData/Local/Programs/Python/Python310/DLLs/Dll_air_transportation.dll")
schedule = my_lib.dll_CreateSchedule()
my_lib.dll_PrintTime(schedule)
my_lib.dll_DeleteSchedule(schedule)
