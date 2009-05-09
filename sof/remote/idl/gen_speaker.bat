idl.exe --c++-suffix=cpp Speaker.idl


copy Speaker.cpp ..\examples\common\src
copy Speaker.h   ..\examples\common\src


del Speaker.cpp 
del Speaker.h 