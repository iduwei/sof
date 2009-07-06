PATH=%PATH%;..\corba\libs

..\corba\bin\idl.exe --c++-suffix=cpp CORBAObjects.idl

copy CORBAObjects.cpp ..\impl\src\sof\framework\remote\corba\generated
copy CORBAObjects.h ..\impl\src\sof\framework\remote\corba\generated


del CORBAObjects.cpp
del CORBAObjects.h

