find_package(SDL2_image REQUIRED)

add_executable(l9 src/main.cpp)
target_link_libraries(l9 SDL2 ${SDL2_IMAGE_LIBRARY})