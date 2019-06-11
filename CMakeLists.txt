cmake_minimum_required(VERSION 2.8)

project(avr-prog-pi)

file(GLOB SOURCES src/*.cpp)
file(GLOB TEST_SOURCES test/*.cpp)
list(REMOVE_ITEM SOURCES src/main.cpp)

file(GLOB LIB_INTEL_HEX_PARSER_SOURCES lib/IntelHexParser/src/*.cpp)
file(GLOB LIB_INTEL_HEX_SOURCES lib/libintelhex/src/*.cc)

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/test/catch.hpp)
    file(DOWNLOAD https://github.com/catchorg/Catch2/releases/download/v2.8.0/catch.hpp ${CMAKE_SOURCE_DIR}/test/catch.hpp SHOW_PROGRESS)
endif()

find_library(BCM2835_LIBRARY NAMES bcm2835 libbcm2835)

if(BCM2835_LIBRARY)
  include_directories(src/bcm2835)
  file(GLOB BCM2835_SOURCES src/bcm2835/*.cpp)
  set(BCM2835_LIBRARIES ${BCM2835_LIBRARY})
else()
  include_directories(src/noop)
  file(GLOB NOOP_SOURCES src/noop/*.cpp)
endif()

include_directories(src)
include_directories(test)

include_directories(lib/IntelHexParser/include)
include_directories(lib/libintelhex/include)

add_library(avrprog STATIC ${SOURCES} ${BCM2835_SOURCES} ${NOOP_SOURCES} ${LIB_INTEL_HEX_PARSER_SOURCES} ${LIB_INTEL_HEX_SOURCES})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} avrprog ${BCM2835_LIBRARIES})

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests avrprog)

enable_testing()
add_test(NAME unit-tests COMMAND tests)
