
if ( WIN32 )
    SET ( ENV{PATH} $ENV{MICO_HOME}\\win32-bin\\lib )
    FIND_PROGRAM( CORBAIDL $ENV{MICO_HOME}/win32-bin/idl )    
endif ( WIN32 )

if ( UNIX )
    SET ( ENV{PATH} $ENV{MICO_HOME}/libs )
    FIND_PROGRAM( CORBAIDL $ENV{MICO_HOME}/idl/idl    )    
    MESSAGE( STATUS ${CORBAIDL} )
endif ( UNIX )

EXECUTE_PROCESS(
    COMMAND ${CORBAIDL} --c++-suffix=cpp --use-quotes CORBAAdminObjects.idl 
    COMMAND ${CORBAIDL} --c++-suffix=cpp --use-quotes CORBAObjects.idl
    RESULT_VARIABLE ret_var )

MESSAGE( STATUS "--> Return value of executed process: -> ${ret_var}")

