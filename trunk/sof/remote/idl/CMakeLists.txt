PROJECT (IDL)

# Calling idl.cmake script because environment variable PATH can be not set for a custom target
ADD_CUSTOM_TARGET( compile_idl
    COMMAND ${CMAKE_COMMAND} -P idl.cmake
    WORKING_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}
    )
   
# old stuff, please remove if idl.cmake script works without any erros   
#FIND_PROGRAM( CORBAIDL $ENV{MICO_HOME}/win-32/idl )   
#ADD_CUSTOM_TARGET( compile_idl
#   COMMAND ${CORBAIDL} --c++-suffix=cpp --use-quotes ${CMAKE_CURRENT_SOURCE_DIR}/CORBAAdminObjects.idl 
#  COMMAND ${CORBAIDL} --c++-suffix=cpp --use-quotes ${CMAKE_CURRENT_SOURCE_DIR}/CORBAObjects.idl
#)  
    
ADD_CUSTOM_COMMAND(
    TARGET compile_idl
   
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/CORBAAdminObjects.cpp
    ${CMAKE_SOURCE_DIR}/remote/impl/src/sof/services/admin/remote/corba/generated/CORBAAdminObjects.cpp
    
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/CORBAAdminObjects.h
    ${CMAKE_SOURCE_DIR}/remote/impl/src/sof/services/admin/remote/corba/generated/CORBAAdminObjects.h

    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/CORBAObjects.cpp
    ${CMAKE_SOURCE_DIR}/remote/impl/src/sof/framework/remote/corba/generated/CORBAObjects.cpp
    
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/CORBAObjects.h
    ${CMAKE_SOURCE_DIR}/remote/impl/src/sof/framework/remote/corba/generated/CORBAObjects.h
)

 


                    





