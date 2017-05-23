cmake_minimum_required(VERSION 3.7.1)
project(teleop)

enable_language(CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-g -Wall")
set (CMAKE_MACOSX_RPATH 1)

set (EXEC execTeleop)
set (LIB_NAME libTeleop)
set (TEST_EXEC testTeleop)
set (CLIENT_EXEC execClient)
set (SERVER_EXEC execServer)

set (INCLUDE_DIRS include)
set (SOURCE src/teleop_main.cpp)

set (LIB_SOURCE	src/input_to_command.cpp
    		src/driver.cpp)
set (SERVER_SOURCE src/blocking_tcp_echo_server.cpp
    		   src/driver.cpp)
set (CLIENT_SOURCE src/blocking_tcp_echo_client.cpp
    		   src/input_to_command.cpp)
set (TEST_SOURCE test/teleop_command_test.cpp
    		 test/driver_test.cpp
		 test/input_to_command_test.cpp)

## For Compiling on Raspberry Pi
option(Raspberry "Raspberry" OFF)

if (Raspberry)
   message("Compiling with wiring libs")
   set (EXTERNAL_DEPS boost_system boost_serialization wiringPi curses)
   add_definitions(-DPI)
else()
   message("Compiling without Pi libraries")
   set (EXTERNAL_DEPS boost_system boost_serialization curses)
endif()

## Google Test Setup
configure_file(CMakeLists.txt.in
               googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
 
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)


find_package(boost)

## Executable strictly for debugging.
add_executable(${EXEC} ${SOURCE})
target_include_directories(${EXEC} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIRS})
target_link_libraries(${EXEC} ${EXTERNAL_DEPS})

## Server Executable (run on Pi)
add_executable(${SERVER_EXEC} ${SERVER_SOURCE})
target_include_directories(${SERVER_EXEC} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIRS})
target_link_libraries(${SERVER_EXEC} ${EXTERNAL_DEPS})

## Client Executable (run on machine)
add_executable(${CLIENT_EXEC} ${CLIENT_SOURCE})
target_include_directories(${CLIENT_EXEC} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIRS})
target_link_libraries(${CLIENT_EXEC} ${EXTERNAL_DEPS})

## Build Library (for GTest)
add_library(${LIB_NAME} ${LIB_SOURCE})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIRS})

## Build Unit Test executable
enable_testing()
add_executable(${TEST_EXEC} ${TEST_SOURCE})
target_link_libraries(${TEST_EXEC} gtest gtest_main)
target_link_libraries(${TEST_EXEC} ${EXTERNAL_DEPS})
target_link_libraries(${TEST_EXEC} ${LIB_NAME})
add_test(NAME gtest-${LIB_NAME} COMMAND ${TEST_EXEC})
