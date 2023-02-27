cmake_minimum_required(VERSION 3.23)
project(noughts_and_crosses)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

set(SDL2_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2/cmake)
set(SDL2_image_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2_image/cmake)
set(SDL2_ttf_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf/cmake)
set(SDL2_mixer_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2_mixer/cmake)

add_executable(
        ${CMAKE_PROJECT_NAME}
        src/main.cpp
        src/constants.h
        src/utils.h
        src/utils.cpp
        src/globals.h src/globals.cpp src/shapeDrawer.h src/shapeDrawer.cpp src/colours.h src/tile.h src/tile.cpp src/states.h src/gameState.h src/tileGenerator.h src/tileGenerator.cpp src/gameState.cpp)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        SDL2::SDL2main
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer
)
