cmake_minimum_required(VERSION 3.9)
project(FFmpegDemo)

set(CMAKE_CXX_STANDARD 11)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
message(STATUS ${CMAKE_MODULE_PATH})
if (FLAG STREQUAL CLION_IDE)
    message(STATUS "clion")
    option(CLION "user clion run function" ON)
else ()
    message(STATUS "not clion")
    option(CLION "user clion run function" OFF)
endif ()
if (CLION)
    set(RES_PATH_CLION 1)
else ()
    set(RES_PATH_BUILD 1)
endif ()
configure_file(
        "${PROJECT_SOURCE_DIR}/Config.h.in"
        "${PROJECT_BINARY_DIR}/Config.h"
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories(include)

add_subdirectory(Twinklebear)

add_subdirectory(lazyfoo)

add_subdirectory(ffmpeg)

add_subdirectory(opengl)