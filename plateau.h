//
// Created by vivie on 15/11/2025.
//

#ifndef TETRIS_PLATEAU_H
#define TETRIS_PLATEAU_H

#include "vertexarray.h"
#include "object.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"

class Plateau
{
public:
    void build(Object o, Camera cam, Shader shader, Renderer renderer, VertexArray va);
};


#endif //TETRIS_PLATEAU_H