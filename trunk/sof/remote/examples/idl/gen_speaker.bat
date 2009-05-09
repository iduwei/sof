idl.exe --c++-suffix=cpp Speaker.idl


copy Speaker.cpp ..\common\src
copy Speaker.h   ..\common\src


del Speaker.cpp 
del Speaker.h 