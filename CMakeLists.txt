cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

file(GLOB CPP_SOURCES "src/*.cpp")

add_executable(x util/main.cpp ${CPP_SOURCES})

find_package(Curses REQUIRED)

target_link_libraries(x PRIVATE ${CURSES_LIBRARIES})
target_include_directories(x PRIVATE ${CURSES_INCLUDE_DIR})
