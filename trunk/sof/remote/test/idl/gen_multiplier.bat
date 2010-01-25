idl.exe --c++-suffix=cpp Multiplier.idl


copy Multiplier.cpp ..\src
copy Multiplier.h   ..\src


del Multiplier.cpp 
del Multiplier.h 