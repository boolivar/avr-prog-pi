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
    src/noop/spifactoryimpl.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(src)
include_directories(src/noop)
