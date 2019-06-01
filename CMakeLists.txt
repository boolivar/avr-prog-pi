cmake_minimum_required(VERSION 2.8)

project(avr-prog-pi)

file(GLOB SOURCES src/*.cpp)
file(GLOB BCM2835_SOURCES src/bcm2835/*.cpp)
file(GLOB NOOP_SOURCES src/noop/*.cpp)
file(GLOB TEST_SOURCES test/*.cpp)

list(REMOVE_ITEM SOURCES src/main.cpp)

file(GLOB LIB_INTEL_HEX_PARSER_SOURCES lib/IntelHexParser/src/*.cpp)
file(GLOB LIB_INTEL_HEX_SOURCES lib/libintelhex/src/*.cc)

include_directories(src)
include_directories(src/noop)
include_directories(test)
#include_directories(src/bcm2835)
#include_directories(src/bcm2835/stub)
include_directories(lib/IntelHexParser/include)
include_directories(lib/libintelhex/include)

add_library(avrprog STATIC ${SOURCES} ${NOOP_SOURCES} ${LIB_INTEL_HEX_PARSER_SOURCES} ${LIB_INTEL_HEX_SOURCES})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} avrprog)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests avrprog)

enable_testing()
add_test(NAME unit-tests COMMAND tests)
