cmake_minimum_required(VERSION 3.16)

project(tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




add_executable(tetris main.cpp camera.cpp camera.h
controls.cpp controls.h fpscontrols.cpp fpscontrols.h navigationcontrols.cpp navigationcontrols.h
object.cpp object.h shader.cpp shader.h texture.cpp texture.h uvbuffer.cpp uvbuffer.h vertexarray.cpp vertexarray.h
vertexbuffer.cpp vertexbuffer.h renderer.cpp renderer.h
        game.cpp
        game.h
        plateau.cpp
        plateau.h)


include(GNUInstallDirs)
install(TARGETS tetris
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
