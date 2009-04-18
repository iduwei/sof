idl.exe --c++-suffix=cpp CORBAObjects.idl

copy CORBAObjects.cpp ..\common\src\sof\framework\remote\corba\generated
copy CORBAObjects.h ..\common\src\sof\framework\remote\corba\generated


del CORBAObjects.cpp
del CORBAObjects.h

