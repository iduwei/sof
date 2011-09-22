PROJECT( CppUnitLite )

set( SOURCES 
  src/Failure.cpp
  src/SimpleString.cpp
  src/Test.cpp
  src/TestRegistry.cpp
  src/TestResult.cpp
)

ADD_LIBRARY( cppunitlite ${SOURCES} )