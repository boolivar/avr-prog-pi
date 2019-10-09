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

set(AVRPROG_LIBS avrprog)

find_library(BCM2835_LIBRARY NAMES bcm2835 libbcm2835)
if(BCM2835_LIBRARY)
    list(APPEND AVRPROG_LIBS ${BCM2835_LIBRARY})
    file(GLOB SPI_SOURCES src/bcm2835/*.cpp)
    include_directories(src/bcm2835)
else()
    file(GLOB SPI_SOURCES src/noop/*.cpp)
    include_directories(src/noop)
endif()

include_directories(src)
include_directories(test)

include_directories(lib/IntelHexParser/include)
include_directories(lib/libintelhex/include)

add_library(avrprog STATIC ${SOURCES} ${SPI_SOURCES} ${LIB_INTEL_HEX_PARSER_SOURCES} ${LIB_INTEL_HEX_SOURCES})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${AVRPROG_LIBS})

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests avrprog)

enable_testing()
add_test(NAME unit-tests COMMAND tests)
