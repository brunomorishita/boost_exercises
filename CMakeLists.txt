cmake_minimum_required(VERSION 2.8)
project(boost-exercises)

if (UNIX)
	message(status "Setting GCC flags")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -g -Wall")
else()
	message(status "Setting MSVC flags")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc-")
endif()
message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)
set(BOOST_ALL_DYN_LINK           ON)   # force dynamic linking for all libraries

find_package(Boost 1.47 COMPONENTS unit_test_framework REQUIRED)
message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
message(status "** Boost Libraries Directories: ${Boost_LIBRARY_DIRS}")
message(status "** Boost Libraries: ${Boost_LIBRARIES}")

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

add_executable(test_sfinae test_sfinae.cpp)
add_executable(ex2_0 ex2_0.cpp)
add_executable(ex2_1 ex2_1.cpp)
add_executable(ex2_2 ex2_2.cpp)
