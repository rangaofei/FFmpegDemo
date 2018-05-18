find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

add_executable(lesson6 src/main.cpp)

target_link_libraries(lesson6 SDL2 ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY})