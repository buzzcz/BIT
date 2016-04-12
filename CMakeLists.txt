cmake_minimum_required(VERSION 3.5)
project(SP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp png_steg.cpp png_steg.h wav_steg.cpp wav_steg.h steg.cpp steg.h)
add_executable(SP ${SOURCE_FILES})

find_package(PNG)
target_link_libraries(SP ${PNG_LIBRARY})

add_custom_command(TARGET SP POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/Bug.png"      # <--this is in-file
        $<TARGET_FILE_DIR:SP>)                 # <--this is out-file path

add_custom_command(TARGET SP POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/NeroSound.wav"      # <--this is in-file
        $<TARGET_FILE_DIR:SP>)                 # <--this is out-file path