cmake_minimum_required(VERSION 3.15)
project(Project2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project2
        asteroids.cpp game_object.cpp ship.cpp ability.cpp ability.h game.h bullet.cpp bullet.h asteroid.cpp asteroid.h)


target_link_libraries(Project2 ${CMAKE_CURRENT_SOURCE_DIR}/Framework/libFrameworkRelease.0.0.1.dylib) # X11)
