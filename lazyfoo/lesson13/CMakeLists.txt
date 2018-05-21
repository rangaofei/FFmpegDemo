find_package(SDL2_image REQUIRED)

add_executable(l13 src/main.cpp src/LTexture.cpp)
target_link_libraries(l13 SDL2 ${SDL2_IMAGE_LIBRARY})