find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

add_executable(lesson5 src/main.cpp)

target_link_libraries(lesson5 SDL2 ${SDL2_IMAGE_LIBRARY})