
cmake_minimum_required (VERSION 3.8)

project(yuvPlayer)

include_directories("../include/SDL")

link_directories("../lib")

add_executable (yuvPlayer "yuvPlayer.cpp")

target_link_libraries(yuvPlayer SDL2 SDL2main SDL2test)
