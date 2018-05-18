find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
add_executable(lesson3 src/main.cpp)
target_link_libraries(lesson3 SDL2 ${SDL2_IMAGE_LIBRARY})