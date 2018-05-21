find_package(SDL2_image REQUIRED)

add_executable(l7 src/main.cpp)
target_link_libraries(l7 SDL2 ${SDL2_IMAGE_LIBRARY})