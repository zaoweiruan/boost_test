cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(recipe-08 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

set(compiler_type "mgw13")


#message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
#if(CMAKE_SIZEOF_VOID_P EQUAL 8)
#    message(STATUS "Target is 64 bits")
#else()
#    message(STATUS "Target is 32 bits")
#endif()

set(boost_lib_prefix "libboost_")

if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL Release)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set(boost_lib_suffix "-mgw13-mt-x64-1_86.a")
else()
	set(boost_lib_suffix "-mgw13-mt-d-x64-1_86.a")
endif()

if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_amd64")
	set(x64_architecture 0)
    #message(STATUS "x86_64 architecture detected")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "AMD64")
    set(x64_architecture 1)
    #message(STATUS "x64 architecture detected")
else()
	set(x64_architecture)
endif()


#set(Boost_ROOT "E:/vcpkg/installed/x64-mingw-dynamic")
set(Boost_ROOT "D:/Boost-1.86.0/")
include_directories(BEFORE "${Boost_ROOT}/include")
link_directories("${Boost_ROOT}/lib")


if (CMAKE_BUILD_TYPE STREQUAL Debug)
set(boost_lib_suffix "-mgw13-mt-d-x64-1_86.a")
message(STATUS "boost_lib_suffix=${boost_lib_suffix}")
else()

message(STATUS "boost_lib_suffix=${boost_lib_suffix}")
endif()

#include(D:/mvnworkspace/buildtype.cmake)

#find_package(Boost 1.86.0 REQUIRED filesystem assert config beast PATHS "E:/vcpkg/installed/x64-mingw-static" )

#find_package(Boost 1.85.0 CONFIG REQUIRED filesystem  PATHS "E:/vcpkg/installed/x64-mingw-dynamic")
#find_package(Boost 1.86.0 CONFIG REQUIRED filesystem PATHS "E:/boost-1.86.0")
#include(D:/mvnworkspace/find_boost.cmake)
add_executable(path-info)
set_target_properties (path-info PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set_target_properties(path-info PROPERTIES SOURCES "${PROJECT_SOURCE_DIR}/src/path_info.cpp")
target_link_libraries(path-info
  PUBLIC
#      Boost::filesystem
      "${boost_lib_prefix}filesystem${boost_lib_suffix}"
   )
    
set(project_target http_server_sync)   
add_executable(${project_target})
set_target_properties (${project_target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set_target_properties(${project_target} PROPERTIES SOURCES "${PROJECT_SOURCE_DIR}/src/${project_target}.cpp")
target_link_libraries(${project_target}
  PUBLIC
#      Boost::filesystem
      ws2_32
   )
unset(project_target)

add_executable(json_client)

set(project_target json_client)   

set_target_properties (${project_target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set_target_properties(${project_target} PROPERTIES SOURCES "${PROJECT_SOURCE_DIR}/src/${project_target}.cpp")
target_link_libraries(${project_target}
  PUBLIC
#      Boost::filesystem
      ws2_32
   )
unset(project_target)