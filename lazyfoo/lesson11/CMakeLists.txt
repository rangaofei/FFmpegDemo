find_package(SDL2_image REQUIRED)

add_executable(l11 src/main.cpp src/LTexture.cpp)
target_link_libraries(l11 SDL2 ${SDL2_IMAGE_LIBRARY})