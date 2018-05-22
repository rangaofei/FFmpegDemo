find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_executable(l25 src/main.cpp src/LTexture.cpp src/LTimer.cpp)
target_link_libraries(l25 SDL2
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${SDL2_MIXER_LIBRARY})