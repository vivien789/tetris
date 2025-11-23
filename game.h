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
    void deleteLine();
    void descendLine(Camera cam, Shader shader, Renderer renderer, VertexArray va);
    bool isLign();
    bool borderTest(Object piece);
    std::list<Object> stock;
    std::list<int> zDeleted;
};


#endif //TETRIS_GAME_H