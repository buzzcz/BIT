cmake_minimum_required(VERSION 3.5)
project(SP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp png.cpp png.h wav.cpp wav.h crc_calc.cpp crc_calc.h)
add_executable(SP ${SOURCE_FILES})

add_custom_command(TARGET SP POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/Bug.png"      # <--this is in-file
        $<TARGET_FILE_DIR:SP>)                 # <--this is out-file path