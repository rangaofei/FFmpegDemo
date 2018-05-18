cmake_minimum_required(VERSION 3.10)
project(FFmpegDemo)

set(CMAKE_CXX_STANDARD 11)

add_executable(FFmpegDemo1 FFmpegDemo1.c)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

if (FLAG STREQUAL CLION_IDE)
    message(STATUS "clion")
    option(CLION "user clion run function" ON)
else ()
    message(STATUS "not clion")
    option(CLION "user clion run function" OFF)
endif ()
if (CLION)
    set(CLION 1)
    configure_file(
            "${PROJECT_SOURCE_DIR}/Config.h.in"
            "${PROJECT_BINARY_DIR}/Config.h"
    )
endif ()
include_directories("${PROJECT_BINARY_DIR}")
include_directories(include)

add_subdirectory(Twinklebear)

add_subdirectory(lazyfoo)

target_link_libraries(FFmpegDemo1
        avformat
        z
        m
        pthread
        avdevice
        avfilter
        avcodec
        avutil
        #        postproc
        swresample
        swscale
        dl
        )

add_executable(FFmpegDemo2 FFmpegDemo2.c)
target_link_libraries(FFmpegDemo2
        avformat
        z
        m
        pthread
        avdevice
        avfilter
        avcodec
        avutil
        #        postproc
        swresample
        swscale
        dl
        SDL2
        )