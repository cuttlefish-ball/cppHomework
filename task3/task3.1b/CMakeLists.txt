cmake_minimum_required(VERSION 3.2)

project(mp4Player)

include_directories("../include/SDL")
include_directories("../include/ffmpeg")

link_directories("../lib/SDL")
link_directories("../lib/ffmpeg")

add_executable(${PROJECT_NAME} mp4Player.cpp)

target_link_libraries(${PROJECT_NAME}   
        avformat
        avcodec
        avutil
        SDL2 
        SDL2main 
        SDL2test)