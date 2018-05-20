find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
MESSAGE(STATUS ${SDL2_IMAGE_LIBRARY})
add_executable(lesson4 src/main.cpp)

target_link_libraries(lesson4 SDL2 ${SDL2_IMAGE_LIBRARY})