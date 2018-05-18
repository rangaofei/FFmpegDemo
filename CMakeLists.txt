cmake_minimum_required(VERSION 3.10)
project(FFmpegDemo)

set(CMAKE_CXX_STANDARD 11)

add_executable(FFmpegDemo1 FFmpegDemo1.c)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

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