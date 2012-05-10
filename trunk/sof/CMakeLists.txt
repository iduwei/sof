cmake_minimum_required(VERSION 2.6)

if ( UNIX )
    # preprocessor definition
    ADD_DEFINITIONS( -DUNIX )
 
    #necessary for dlopen, dlsym calls etc.
    LINK_LIBRARIES(${CMAKE_THREAD_LIBS} ${CMAKE_DL_LIBS})
 
    # Types of dynamic libraries are hidden
    SET( CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden" )
    
    # setting CORBA MICO libraries directory
    SET_PROPERTY ( GLOBAL PROPERTY MICO_LIBS $ENV{MICO_HOME}/libs )
    
    # setting name of MICO ORB library (differs between UNIX and Windows)
    SET_PROPERTY ( GLOBAL PROPERTY MICO_ORB mico2.3.13 )
    
    # setting name of MICO naming library (differs between UNIX and Windows)
    SET_PROPERTY ( GLOBAL PROPERTY MICO_COSS micocoss2.3.13 )
    
    # setting name pthread library (differs between UNIX and Windows)
    SET_PROPERTY ( GLOBAL PROPERTY MICO_PTHREAD "-pthread" )
    
    # sof_remote_test run script
    SET_PROPERTY ( GLOBAL PROPERTY SOF_REMOTE_TEST_SCRIPT "run_remote_test.sh" )    
    
    # sof_remote_console run script
    SET_PROPERTY ( GLOBAL PROPERTY SOF_REMOTE_CONSOLE_SCRIPT "run_remote_console.sh" ) 
    
    # sof_remote_console run script without using the CORBA naming service
    SET_PROPERTY ( GLOBAL PROPERTY SOF_REMOTE_CONSOLE__NO_NS_SCRIPT "run_remote_console_no_ns.sh" ) 
    
    # naming service run script
    SET_PROPERTY ( GLOBAL PROPERTY SOF_NAMING_SERVICE_SCRIPT "run_ns.sh" ) 
    
    # naming service admin run script
    SET_PROPERTY ( GLOBAL PROPERTY SOF_NAMING_SERVICE_ADMIN_SCRIPT "run_nsadmin.sh" ) 
    
    # naming service admin run script
    SET_PROPERTY ( GLOBAL PROPERTY SOF_REGISTRY_SCRIPT "run_registry.sh" ) 
    
    # naming service admin run script without using the CORBA naming service
    SET_PROPERTY ( GLOBAL PROPERTY SOF_REGISTRY_NO_NS_SCRIPT "run_registry_no_ns.sh" ) 
    
    # MICO include directory
    SET_PROPERTY ( GLOBAL PROPERTY MICO_INCLUDE $ENV{MICO_HOME}/include ) 
    
endif ( UNIX )

if ( WIN32 )
    ADD_DEFINITIONS( -DWIN32 )
    
    # setting CORBA MICO libraries directory
    SET_PROPERTY ( GLOBAL PROPERTY MICO_LIBS $ENV{MICO_HOME}/win32-bin/lib )
    
    # setting CORBA MICO bin directory
    SET_PROPERTY ( GLOBAL PROPERTY MICO_BIN $ENV{MICO_HOME}/win32-bin )
    
    # setting name of MICO ORB library (differs between UNIX and Windows)
    SET_PROPERTY ( GLOBAL PROPERTY MICO_ORB mico2313 ) 
    
    # setting name of MICO naming library (differs between UNIX and Windows)
    SET_PROPERTY ( GLOBAL PROPERTY MICO_COSS micocoss2313 )
    
    # setting name pthread library (differs between UNIX and Windows)
    if ( CMAKE_BUILD_TYPE MATCHES Debug )
        MESSAGE( STATUS debug )
        SET_PROPERTY ( GLOBAL PROPERTY MICO_PTHREAD pthreadVC2d )
    else ( CMAKE_BUILD_TYPE MATCHES Debug )
        MESSAGE( STATUS release )
        SET_PROPERTY ( GLOBAL PROPERTY MICO_PTHREAD pthreadVC2 )
    endif ( CMAKE_BUILD_TYPE MATCHES Debug )
    
    # sof_remote_test run script
    SET_PROPERTY ( GLOBAL PROPERTY SOF_REMOTE_TEST_SCRIPT "run_remote_test.bat" )  
    
    # sof_remote_console run script
    SET_PROPERTY ( GLOBAL PROPERTY SOF_REMOTE_CONSOLE_SCRIPT "run_remote_console.bat" )  
    
    # sof_remote_console run script without using the CORBA naming service
    SET_PROPERTY ( GLOBAL PROPERTY SOF_REMOTE_CONSOLE__NO_NS_SCRIPT "run_remote_console_no_ns.bat" ) 
    
    # naming service run script
    SET_PROPERTY ( GLOBAL PROPERTY SOF_NAMING_SERVICE_SCRIPT "run_ns.bat" ) 
    
    # naming service admin run script
    SET_PROPERTY ( GLOBAL PROPERTY SOF_NAMING_SERVICE_ADMIN_SCRIPT "run_nsadmin.bat" ) 
    
    # naming service admin run script
    SET_PROPERTY ( GLOBAL PROPERTY SOF_REGISTRY_SCRIPT "run_registry.bat" ) 
    
    # naming service admin run script without using the CORBA naming service
    SET_PROPERTY ( GLOBAL PROPERTY SOF_REGISTRY_NO_NS_SCRIPT "run_registry_no_ns.bat" ) 
    
    # MICO include directory
    SET_PROPERTY ( GLOBAL PROPERTY MICO_INCLUDE $ENV{MICO_HOME}/include $ENV{MICO_HOME}/contrib/pthreads ) 
    
endif ( WIN32 )

if ( SOF_REMOTE )
    MESSAGE( STATUS "Build Remote SOF" )
    SUBDIRS(
        impl 
        extern/CppUnitLite 
        console 
        examples 
        examples/bundle1 
        examples/bundle2 
        remote/impl 
        remote/console 
        remote/registry 
        remote/idl
        test 
        test/TestDll1 
        test/TestDll2 
        remote/test
        remote/examples/bundle1
        remote/examples/bundle2
    )
else ( SOF_REMOTE )
    MESSAGE( STATUS "Build SOF" )
    SUBDIRS(
        impl 
        extern/CppUnitLite 
        console 
        examples 
        examples/bundle1 
        examples/bundle2 
        test 
        test/TestDll1 
        test/TestDll2 
    )
endif ( SOF_REMOTE )


# add a target to generate API documentation with Doxygen
FIND_PACKAGE( Doxygen )
if(DOXYGEN_FOUND)
    file( MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/api/sof )
    file( MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/api/sof_remote )
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen/Doxyfile_remote ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile_remote @ONLY)
    ADD_CUSTOM_TARGET(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating SOF API documentation with Doxygen" VERBATIM
        )
    ADD_CUSTOM_TARGET(doc_remote
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile_remote
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating Remote SOF API documentation with Doxygen" VERBATIM
        )
else (DOXYGEN_FOUND)
    MESSAGE( STATUS "Doxygen NOT found." )
endif(DOXYGEN_FOUND)
