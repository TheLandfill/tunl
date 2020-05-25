cmake_minimum_required(VERSION 3.0.0)
project(tunl)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Bring the headers, such as Student.h into the project
include_directories(${CMAKE_SOURCE_DIR}/includes)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/*.cpp")

#Generate the static library from the sources
add_library(tunl STATIC ${SOURCES})

add_executable(run-tunl-tests ${TEST_SOURCES})

target_link_libraries(run-tunl-tests tunl)
