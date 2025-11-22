#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <list>

#include "vertexarray.h"
#include "object.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"

class Game
{
public:
    Game();
    Object choosePiece(Object piece);
    void renderPiece(Object piece, Camera cam, Shader shader, Renderer renderer, VertexArray va);
    void saveInStock(Object piece, Camera cam, Shader shader, Renderer renderer, VertexArray va);
    void deleteLine(Camera cam, Shader shader, Renderer renderer, VertexArray va);
    bool isLign();
    std::list<Object> stock;
};


#endif //TETRIS_GAME_H