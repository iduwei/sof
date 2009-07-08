PATH=%PATH%;..\..\corba\libs

..\..\corba\bin\idl.exe --c++-suffix=cpp Multiplier.idl


copy Multiplier.cpp ..\common\src
copy Multiplier.h   ..\common\src


del Multiplier.cpp 
del Multiplier.h 