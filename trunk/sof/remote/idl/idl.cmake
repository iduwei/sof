
if ( WIN32 )
    SET ( ENV{PATH} $ENV{MICO_HOME}\\win32-bin\\lib )
    FIND_PROGRAM( CORBAIDL $ENV{MICO_HOME}/win32-bin/idl )    
endif ( WIN32 )

if ( UNIX )
    SET ( ENV{LD_LIBRARY_PATH} $ENV{MICO_HOME}/libs)
    SET ( ENV{PATH} $ENV{MICO_HOME}/cpp)
    FIND_PROGRAM( CORBAIDL $ENV{MICO_HOME}/idl/idl )   
endif ( UNIX )

EXECUTE_PROCESS(
    COMMAND ${CORBAIDL} --c++-suffix=cpp --use-quotes CORBAAdminObjects.idl 
    COMMAND ${CORBAIDL} --c++-suffix=cpp --use-quotes CORBAObjects.idl
    RESULT_VARIABLE ret_var )


   

