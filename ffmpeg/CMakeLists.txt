add_executable(FFmpegDemo1 FFmpegDemo1.c)
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