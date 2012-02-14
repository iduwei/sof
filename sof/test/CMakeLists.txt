PROJECT (SOF_TEST)

SET (SOURCES 
    src/TestHelper.cpp
	src/BaseTestClass.cpp
	src/ConfigFileReaderTest.cpp
	src/IServiceBImpl.cpp
	src/ITestImpl.cpp
	src/ObjectCreatorTest.cpp
	src/osgi_sof_test.cpp
	src/ServiceListenerNotificationTest.cpp
	src/ServiceListenerRegistrationTest.cpp
	src/ServiceListenerNotificationErrorTest.cpp
	src/TestBundleActivator.cpp
	src/TestClass.cpp
	src/ThreadingTest.cpp
	src/UnitTestLogger.cpp
	src/LauncherTest.cpp
	)
    
INSTALL( FILES ${CMAKE_SOURCE_DIR}/test/config/config_file_reader_test.sof DESTINATION ${CMAKE_BINARY_DIR}/test )
INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/impl/src ${CMAKE_SOURCE_DIR}/extern/CppUnitLite/src )
LINK_DIRECTORIES( ${CMAKE_BINARY_DIR}/impl ${CMAKE_BINARY_DIR}/extern/CppUnitLite )


ADD_EXECUTABLE( sof_test ${SOURCES} )

TARGET_LINK_LIBRARIES( sof_test sof cppunitlite )
ADD_DEPENDENCIES( sof_test sof_TestDll1 sof_TestDll2 )



