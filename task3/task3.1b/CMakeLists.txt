cmake_minimum_required(3.2)

project(mp4Player)

include_directories("../include/SDL" "../include/ffmpeg")

link_directories("../lib/SDL" "../lib/ffmpeg")

add_executable(mp4Player.cpp)