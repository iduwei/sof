PROJECT (SOF_EXAMPLES)

SET (SOURCES 
	src/sof_examples.cpp
	)
    

INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/impl/src )
LINK_DIRECTORIES( ${CMAKE_BINARY_DIR}/impl )


ADD_EXECUTABLE( sof_examples ${SOURCES} )
TARGET_LINK_LIBRARIES( sof_examples sof )
ADD_DEPENDENCIES( sof_examples sof_examples_bundle1 sof_examples_bundle2 )
