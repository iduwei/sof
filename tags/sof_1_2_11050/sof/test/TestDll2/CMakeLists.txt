PROJECT (SOF_TEST_DLL2)

SET (SOURCES 
    src/dll_test.cpp
	src/BundleActivator2.cpp
	src/IServiceAImpl.cpp
	)
    
INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/impl/src ${CMAKE_SOURCE_DIR}/test/src )
LINK_DIRECTORIES( ${CMAKE_BINARY_DIR}/impl )


ADD_LIBRARY( sof_TestDll2 SHARED ${SOURCES} )

if ( UNIX )
    SET_TARGET_PROPERTIES( sof_TestDll2 PROPERTIES 
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test
    )   
endif ( UNIX )

if ( WIN32 )
    SET_TARGET_PROPERTIES( sof_TestDll2 PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test
    )   
endif ( WIN32 )

TARGET_LINK_LIBRARIES( sof_TestDll2 sof )



