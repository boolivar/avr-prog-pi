cmake_minimum_required(VERSION 2.8)

project(avr-prog-pi)

set(SOURCES
    src/avrprogrammer.cpp
    src/chipselect.cpp
    src/datareader.cpp
    src/instructionexecutor.cpp
    src/instructionfactory.cpp
    src/main.cpp
    src/memoryprogrammer.cpp
    src/outputcontroller.cpp
    src/pagememoryprogrammer.cpp
    src/printchipselect.cpp
    src/printspi.cpp
    src/rawdatareader.cpp
    src/serialcontroller.cpp
    src/spi.cpp
    src/spifactory.cpp
    )

set(BCM2835_SOURCES
    src/bcm2835/bcm2835chipselect.cpp
    src/bcm2835/bcm2835spi.cpp
    src/bcm2835/spifactoryimpl.cpp
    )

set(NOOP_SOURCES
    src/noop/spifactoryimpl.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

target_sources(${PROJECT_NAME} PRIVATE ${NOOP_SOURCES})

include_directories(src)
include_directories(src/noop)
