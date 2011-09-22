PROJECT (REMOTE_SOF)
    
SET (SOF_REMOTE_SOURCES 
	src/sof/framework/remote/corba/CORBAHelper.cpp
    src/sof/framework/remote/corba/IRemoteBundleContextImpl.cpp
    src/sof/framework/remote/corba/RemoteBundleInfo.cpp
    src/sof/framework/remote/corba/RemoteServiceEvent.cpp
    src/sof/framework/remote/corba/RemoteServiceInfo.cpp
    src/sof/framework/remote/corba/RemoteServiceListenerInfo.cpp
    src/sof/framework/remote/corba/RemoteServiceReference.cpp
    src/sof/framework/remote/corba/RemoteServiceTracker.cpp
    src/sof/framework/remote/corba/LocalServiceTracker.cpp    
    src/sof/framework/remote/corba/generated/CORBAObjects.cpp
    src/sof/framework/remote/corba/namingservice/CORBANamingServiceFactory.cpp
    src/sof/framework/remote/corba/namingservice/CORBANamingServiceImpl.cpp
    src/sof/framework/remote/corba/registry/CORBARegistryObserverImpl.cpp
    src/sof/framework/remote/corba/registry/IRegistryFacadeImpl.cpp
    src/sof/services/admin/remote/RemoteAdministrationActivator.cpp
    src/sof/services/admin/remote/corba/CORBAAdminServiceImpl.cpp
    src/sof/services/admin/remote/corba/DataConverter.cpp
    src/sof/services/admin/remote/corba/generated/CORBAAdminObjects.cpp
 )

ADD_LIBRARY( sof_remote STATIC ${SOF_REMOTE_SOURCES} )

GET_PROPERTY( MICO_INCLUDE_DIR GLOBAL PROPERTY MICO_INCLUDE )

INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/impl/src ${MICO_INCLUDE_DIR} )

GET_PROPERTY( MICO_LIBRARY_PATH GLOBAL PROPERTY MICO_LIBS )

LINK_DIRECTORIES( ${CMAKE_BINARY_DIR}/impl ${MICO_LIBRARY_PATH} )

TARGET_LINK_LIBRARIES( sof_remote sof )