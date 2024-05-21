cmake_minimum_required(VERSION 3.23)
project(pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

set(SDL2_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2/cmake)
set(SDL2_ttf_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf/cmake)

add_executable(
        ${CMAKE_PROJECT_NAME}
        src/main.cpp
        src/config/constants.h
        src/config/colors.h
        src/globals.h
        src/globals.cpp
        src/utils/utils.h
        src/utils/utils.cpp
        src/game/paddle.h
        src/game/paddle.cpp
        src/game/ball.h
        src/game/ball.cpp
        src/game/player.h
        src/game/player.cpp
        src/game/cpuPlayer.h
        src/game/cpuPlayer.cpp
        src/core/score.h
        src/utils/textTexture.h
        src/utils/textTexture.cpp
        src/ui/scoreUi.cpp
        src/ui/scoreUi.h
        src/core/gameState.h
        src/core/inGameState.cpp
        src/core/inGameState.h
        src/core/inGameState.h
)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        SDL2::SDL2main
        SDL2::SDL2
        SDL2_ttf::SDL2_ttf
)
