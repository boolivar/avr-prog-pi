cmake_minimum_required(VERSION 2.8)

project(avr-prog-pi)

file(GLOB SOURCES src/*.cpp)

file(GLOB BCM2835_SOURCES src/bcm2835/*.cpp)

file(GLOB NOOP_SOURCES src/noop/*.cpp)

file(GLOB LIB_INTEL_HEX_SOURCES lib/IntelHexParser/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${LIB_INTEL_HEX_SOURCES})

target_sources(${PROJECT_NAME} PRIVATE ${NOOP_SOURCES})
#target_sources(${PROJECT_NAME} PRIVATE ${BCM2835_SOURCES})

include_directories(src)
include_directories(src/noop)
#include_directories(src/bcm2835)
#include_directories(src/bcm2835/stub)
include_directories(lib/IntelHexParser/include)
