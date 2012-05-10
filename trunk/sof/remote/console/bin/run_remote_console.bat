PATH=%PATH%;%MICO_HOME%\win32-bin\lib;%MICO_HOME%\win32-bin

sof_remote_console.exe  -ORBNamingAddr inet:localhost:5000 %1 %2
