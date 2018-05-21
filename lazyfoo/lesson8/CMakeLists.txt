find_package(SDL2_image REQUIRED)

add_executable(l8 src/main.cpp)
target_link_libraries(l8 SDL2 ${SDL2_IMAGE_LIBRARY})