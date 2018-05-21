find_package(SDL2_image REQUIRED)

add_executable(l15 src/main.cpp src/LTexture.cpp)
target_link_libraries(l15 SDL2 ${SDL2_IMAGE_LIBRARY})