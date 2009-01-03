idl.exe --c++-suffix=cpp RemoteRegistry.idl

copy RemoteRegistry.cpp ..\common\src\sof\framework\remote\corba\registry\generated
copy RemoteRegistry.h ..\common\src\sof\framework\remote\corba\registry\generated


del RemoteRegistry.cpp
del RemoteRegistry.h

