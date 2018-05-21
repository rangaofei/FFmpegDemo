find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(l18 src/main.cpp src/LTexture.cpp)
target_link_libraries(l18 SDL2 ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})