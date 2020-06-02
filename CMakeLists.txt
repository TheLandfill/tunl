cmake_minimum_required(VERSION 3.0.0)
project(tunl)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/includes)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_library(tunl STATIC ${SOURCES})

add_executable(integration-test "${CMAKE_SOURCE_DIR}/tests/integration.cpp")
add_executable(complex-test "${CMAKE_SOURCE_DIR}/tests/complex.cpp")

target_link_libraries(integration-test tunl)
