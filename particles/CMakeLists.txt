cmake_minimum_required(VERSION 3.23)
project(particles)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

set(SDL2_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2/cmake)
set(SDL2_ttf_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf/cmake)

add_executable(
        ${CMAKE_PROJECT_NAME}
        src/main.cpp
        src/config/config.h
        src/config/colors.h
        src/globals.h
        src/globals.cpp
        src/utils/utils.h
        src/utils/utils.cpp
        src/math/Vector.h
        src/math/Vector.cpp
        src/entities/particle.h
        src/entities/particle.cpp
        src/constants.h
        src/utils/shapes.h
        src/utils/shapes.cpp
        src/entities/simulation.h
        src/entities/simulation.cpp
)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        SDL2::SDL2main
        SDL2::SDL2
        SDL2_ttf::SDL2_ttf
)
