cmake_minimum_required(VERSION 3.16)

project(tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(tetris main.cpp camera.cpp camera.h
controls.cpp controls.h fpscontrols.cpp fpscontrols.h navigationcontrols.cpp navigationcontrols.h
object.cpp object.h shader.cpp shader.h texture.cpp texture.h uvbuffer.cpp uvbuffer.h vertexarray.cpp vertexarray.h
vertexbuffer.cpp vertexbuffer.h renderer.cpp renderer.h stb_image/stb_image.cpp stb_image/stb_image.h
        game.cpp
        game.h
        plateau.cpp
        plateau.h)


include(GNUInstallDirs)
target_link_libraries(tetris glfw GLEW::GLEW opengl32)
install(TARGETS tetris
    RUNTIME DESTINATION bin
)
