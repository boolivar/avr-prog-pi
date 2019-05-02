cmake_minimum_required(VERSION 2.8)

project(avr-prog-pi)

set(SOURCES
    src/main.cpp
    src/spi.cpp
    src/printspi.cpp
    src/chipselect.cpp
    src/printchipselect.cpp
    src/serialcontroller.cpp
    src/pagememoryprogrammer.cpp
    src/instructionfactory.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(src)
