cmake_minimum_required(VERSION 3.3)
project(cslack)

find_package(Curses REQUIRED)

include_directories(${CURSESW_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Logger.cpp src/Logger.h src/Window.cpp src/Window.h src/Display.cpp src/Display.h src/Exception.cpp src/Exception.h src/StatusWindow.cpp src/TextWindow.cpp src/InputWindow.cpp)
add_executable(cslack ${SOURCE_FILES})

target_link_libraries(cslack ${CURSES_LIBRARIES})

