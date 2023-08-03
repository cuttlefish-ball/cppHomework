cmake_minimum_required (VERSION 3.8)

project ("task3.2")

link_directories("../lib/openal")

include_directories("../include/openal")

add_executable (task3.2 "PCMPlayer.cpp" )

target_link_libraries(${PROJECT_NAME} OpenAL32)