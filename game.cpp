#include "game.h"
#include <random>
#include <iostream>


Game::Game()
{
    stock = {};
    zDeleted = {};
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

//Rendu visuel des pièces
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
    renderer.Draw(va, piece, shader);
}

//Liste d'objets : ajout d'une nouvelle pièce avec ses coordonnées
void Game::saveInStock(Object piece, Camera cam, Shader shader, Renderer renderer, VertexArray va)
{
    stock.insert(stock.begin(), piece);
    for (auto p : stock)
    {
        renderPiece(p, cam, shader, renderer, va);
    }

}

//Vrai si au moins une ligne est complète, faux sinon
bool Game::isLign()
{
    bool detect = false;
    //Tester pour chaque hauteur du plateau
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
        //Tester si toutes les positions en x sont occupées
        if (posX.size() == 10)
        {
            detect = true;
            for (auto p : stock)
            {
                if (p.position.z == z)
                {
                    p.toDelete = true;
                    zDeleted.push_back(z);
                }
            }
        }
    }

    return detect;
}

//Supprimer les lignes complètes via l'attribut "toDelete"
void Game::deleteLine()
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
}

//Tester si la pièce a atteint le bord
bool Game::borderTest(Object piece)
{
    bool res = false;
    if (piece.position.z == 2)
    {
        res = true;
    }
    for (auto obj : stock)
    {
        if (obj.position.x == piece.position.x &&  obj.position.z == piece.position.z - 1 )
        {
            res = true;
        }
    }
    return res;
}

//Descendre les pièces une fois les lignes supprimées
void Game::descendLine(Camera cam, Shader shader, Renderer renderer, VertexArray va)
{
    for (auto p : stock)
    {
        for (auto zDel : zDeleted)
        {
            if (p.position.z > zDel)
            {
                p.descend();
            }
        }
        renderPiece(p, cam, shader, renderer, va);
    }
    //Réinitialiser l'attribut zDeleted
    zDeleted.clear();
}