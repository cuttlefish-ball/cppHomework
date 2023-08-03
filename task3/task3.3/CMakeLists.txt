cmake_minimum_required(VERSION 3.0)

project(Player)

include_directories("../include/SDL")
include_directories("../include/ffmpeg")
include_directories("../include/openal")

link_directories("../lib/SDL")
link_directories("../lib/ffmpeg")
link_directories("../lib/openal")

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}   
        avformat
        avcodec
        avutil
        SDL2 
        SDL2main 
        SDL2test
        OpenAL32)