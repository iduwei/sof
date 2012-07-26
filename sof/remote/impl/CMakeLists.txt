PROJECT (REMOTE_SOF)
    
# SET_SOURCE_FILES_PROPERTIES( 
#    src/sof/framework/remote/corba/generated/CORBAObjects.cpp 
#    src/sof/services/admin/remote/corba/generated/CORBAAdminObjects.cpp 
#    PROPERTIES GENERATED TRUE )

SET( GENERATED_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sof/services/admin/remote/corba/generated/CORBAAdminObjects.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sof/framework/remote/corba/generated/CORBAObjects.cpp 
    )
    
SET_SOURCE_FILES_PROPERTIES ( 
    ${GENERATED_SRC} PROPERTIES GENERATED true )
    
SET (SOF_REMOTE_SOURCES 
    ${GENERATED_SRC}
	src/sof/framework/remote/corba/CORBAHelper.cpp
    src/sof/framework/remote/corba/IRemoteBundleContextImpl.cpp
    src/sof/framework/remote/corba/RemoteBundleInfo.cpp
    src/sof/framework/remote/corba/RemoteServiceEvent.cpp
    src/sof/framework/remote/corba/RemoteServiceInfo.cpp
    src/sof/framework/remote/corba/RemoteServiceListenerInfo.cpp
    src/sof/framework/remote/corba/RemoteServiceReference.cpp
    src/sof/framework/remote/corba/RemoteServiceTracker.cpp
    src/sof/framework/remote/corba/LocalServiceTracker.cpp    
    src/sof/framework/remote/corba/namingservice/CORBANamingServiceFactory.cpp
    src/sof/framework/remote/corba/namingservice/CORBANamingServiceImpl.cpp
    src/sof/framework/remote/corba/registry/CORBARegistryObserverImpl.cpp
    src/sof/framework/remote/corba/registry/IRegistryFacadeImpl.cpp
    src/sof/services/admin/remote/RemoteAdministrationActivator.cpp
    src/sof/services/admin/remote/corba/CORBAAdminServiceImpl.cpp
    src/sof/services/admin/remote/corba/DataConverter.cpp
 )
 
ADD_LIBRARY( sof_remote STATIC ${SOF_REMOTE_SOURCES} )

ADD_DEPENDENCIES( sof_remote compile_idl )

GET_PROPERTY( MICO_INCLUDE_DIR GLOBAL PROPERTY MICO_INCLUDE )

INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/impl/src ${MICO_INCLUDE_DIR} )

GET_PROPERTY( MICO_LIBRARY_PATH GLOBAL PROPERTY MICO_LIBS )

LINK_DIRECTORIES( ${CMAKE_BINARY_DIR}/impl ${MICO_LIBRARY_PATH} )

TARGET_LINK_LIBRARIES( sof_remote sof )