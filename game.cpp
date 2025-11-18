//
// Created by vivie on 15/11/2025.
//

#include "game.h"
#include <random>
#include <iostream>


Game::Game()
{
    stock = {};
}

Object Game::choosePiece(Object piece)
{
    std::string tab[7] = {"tquadri", "baton","carre", "lgauche", "ldroite", "zgauche", "zdroite"};
    int indice = std::rand()%(sizeof(tab)/sizeof(tab[0]));
    std::string type = tab[indice];
    piece.position = glm::vec3(11,0,24);

    if (type == "tquadri")
    {
        return piece.getTquadri();
    }
    if (type == "baton")
    {
        return piece.getBaton();
    }
    if (type == "carre")
    {
        return piece.getCarre();
    }
    if (type == "lgauche")
    {
        return piece.getLgauche();
    }
    if (type == "ldroite")
    {
        return piece.getLdroite();
    }
    if (type == "zgauche")
    {
        return piece.getZgauche();
    }
    if (type == "zdroite")
    {
        return piece.getZdroite();
    }
}

void Game::renderPiece(Object piece, Camera cam, Shader shader, Renderer renderer, VertexArray va)
{
    glm::mat4 m;
    glm::mat4 v;
    glm::mat4 p;
    glm::mat4 mvp;

    cam.computeMatrices(600, 600);
    m = piece.getModelMatrix();
    v = cam.getViewMatrix();
    p = cam.getProjectionMatrix();

    mvp = p*v*m;
    shader.setUniformMat4f("MVP", mvp);
    renderer.Clear();
    renderer.Draw(va, piece, shader);
}

void Game::saveInStock(Object piece, Camera cam, Shader shader, Renderer renderer, VertexArray va)
{
    stock.insert(stock.begin(), piece);
    for (auto p : stock)
    {
        renderPiece(p, cam, shader, renderer, va);
    }

}

bool Game::isLign()
{
    bool detect = false;
    for (int z=2; z<=24; z+2)
    {
        std::list<int> posX;
        for (auto p : stock)
        {
            if (p.position.z == z)
            {
                posX.push_back(p.position.x);
            }
        }
        posX.unique();
        if (posX.size() == 10)
        {
            detect = true;
            for (auto p : stock)
            {
                if (p.position.z == z)
                {
                    p.toDelete = true;
                }
            }
        }
    }

    return detect;
}

void Game::deleteLine(Camera cam, Shader shader, Renderer renderer, VertexArray va)
{
    for (std::list<Object>::iterator it = stock.begin(); it != stock.end();)
    {
        if (it->toDelete == true)
        {
            stock.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto p : stock)
    {
        renderPiece(p, cam, shader, renderer, va);
    }
}



