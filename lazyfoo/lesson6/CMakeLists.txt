find_package(SDL2_image REQUIRED)

add_executable(l6 src/main.cpp)
target_link_libraries(l6 SDL2 ${SDL2_IMAGE_LIBRARY})