#include "object.h"

#include <iostream>
#include <random>
#include "renderer.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL

#include <exception>


Object::Object(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::string texturePath):m_vb(0), m_uvsb(0), m_texture(0), position(0,0,0), rotationAngles(0,0,0), vertices(vertices), uvs(uvs)
{

    m_vb = new VertexBuffer(vertices);
    m_uvsb = new UVBuffer(uvs);
    m_texture = new Texture(texturePath);
    toDelete = false;

}


Object::~Object()
{
    delete m_vb;
    if (m_uvsb) delete m_uvsb;
    if (m_texture) delete m_texture;
}

void Object::Bind() const
{
    m_vb->Bind(0);
    if (m_uvsb) m_uvsb->Bind(1);
    if (m_texture) m_texture->Bind(0);
}

void Object::Unbind() const
{
    m_vb->Unbind();
    if (m_uvsb) m_uvsb->Unbind();
    if (m_texture) m_texture->Unbind();
}



void Object::Draw() const
{
    GLCall(glDrawArrays(GL_TRIANGLES,0, m_vb->getSize()));
}

glm::mat4 Object::getModelMatrix()
{
    glm::mat4 m = glm::rotate(glm::translate(glm::mat4(1), position), rotationAngles.x, glm::vec3(1,0,0));
    m=glm::rotate(m, rotationAngles.y, glm::vec3(0,1,0));
    m=glm::rotate(m, rotationAngles.z, glm::vec3(0,0,1));
    return m;
}

glm::vec3 Object::getPosition() const
{
    return position;
}

//Descendre l'objet
void Object::descend()
{
    position.z = position.z - 2;
}

//Tourner l'objet d'un angle de 90 degrés
void Object::rotation()
{
    rotationAngles.y = rotationAngles.y + glm::radians(90.0);
}

//Déplacer l'objet sur la gauche
void Object::moveLeft()
{
    if (position.x >= 2)
    {
        position.x = position.x - 2;
    }
    else //empêcher le déplacement infini vers la gauche
    {
        position.x = 0;
    }
}

//Déplacer l'objet sur la droite
void Object::moveRight()
{
    if (position.x <= 18)
    {
        position.x = position.x + 2;
    }
    else //empêcher le déplacement infini vers la droite
    {
        position.x = 20;
    }
}

//Dessiner chaque pièces
Object Object::getBaton()
{
    std::vector<glm::vec3> ver;
    std::vector<glm::vec2> uv;
    for (int i = 0; i < 4; i++)
    {
        glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3(i * 2, 0, 0));
        for (auto v : vertices)
        {
            glm::vec4 vector = trans * glm::vec4(v, 1.0f);
            ver.push_back(glm::vec3(vector));
        }
    }
    for (auto v : uvs)
    {
        uv.push_back(v);
    }

    return Object(ver, uv, "/textures/texture.jpg");
}

Object Object::getCarre()
{
    std::vector<glm::vec3> ver;
    std::vector<glm::vec2> uv;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3(i * 2, 0, j * 2));
            for (auto v : vertices)
            {
                glm::vec4 vector = trans * glm::vec4(v, 1.0f);
                ver.push_back(glm::vec3(vector));
            }
        }
    }
    for (auto v : uvs)
    {
        uv.push_back(v);
    }

    return Object(ver, uv, "/textures/texture.jpg");
}

Object Object::getLdroite()
{
    std::vector<glm::vec3> ver;
    std::vector<glm::vec2> uv;

    for (int i = 0; i < 3; i++)
    {
        glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3(i * 2, 0, 0));
        for (auto v : vertices)
        {
            glm::vec4 vector = trans * glm::vec4(v, 1.0f);
            ver.push_back(glm::vec3(vector));
        }
    }

    glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3( 4, 0, 2));
    for (auto v : vertices)
    {
        glm::vec4 vector = trans * glm::vec4(v, 1.0f);
        ver.push_back(glm::vec3(vector));
    }

    for (auto v : uvs)
    {
        uv.push_back(v);
    }

    return Object(ver, uv, "/textures/texture.jpg");
}

Object Object::getLgauche()
{
    std::vector<glm::vec3> ver;
    std::vector<glm::vec2> uv;

    glm::mat4 transf = glm::translate(glm::mat4(1), glm::vec3( 0, 0, 2));
    for (auto v : vertices)
    {
        glm::vec4 vector = transf * glm::vec4(v, 1.0f);
        ver.push_back(glm::vec3(vector));
    }

    for (int i = 0; i < 3; i++)
    {
        glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3(i * 2, 0, 0));
        for (auto v : vertices)
        {
            glm::vec4 vector = trans * glm::vec4(v, 1.0f);
            ver.push_back(glm::vec3(vector));
        }
    }

    for (auto v : uvs)
    {
        uv.push_back(v);
    }

    return Object(ver, uv, "/textures/texture.jpg");
}

Object Object::getTquadri()
{
    std::vector<glm::vec3> ver;
    std::vector<glm::vec2> uv;

    glm::mat4 transf = glm::translate(glm::mat4(1), glm::vec3( 2, 0, 2));
    for (auto v : vertices)
    {
        glm::vec4 vector = transf * glm::vec4(v, 1.0f);
        ver.push_back(glm::vec3(vector));
    }

    for (int i = 0; i < 3; i++)
    {
        glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3(i * 2, 0, 0));
        for (auto v : vertices)
        {
            glm::vec4 vector = trans * glm::vec4(v, 1.0f);
            ver.push_back(glm::vec3(vector));
        }
    }

    for (auto v : uvs)
    {
        uv.push_back(v);
    }

    return Object(ver, uv, "/textures/texture.jpg");
}

Object Object::getZdroite()
{
    std::vector<glm::vec3> ver;
    std::vector<glm::vec2> uv;
    for (int i = 0; i < 2; i++)
    {
        glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3(i * 2, 0, 2));
        for (auto v : vertices)
        {
            glm::vec4 vector = trans * glm::vec4(v, 1.0f);
            ver.push_back(glm::vec3(vector));
        }
    }

    for (int j = 1; j < 3; j++)
    {
        glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3(j * 2, 0, 0));
        for (auto v : vertices)
        {
            glm::vec4 vector = trans * glm::vec4(v, 1.0f);
            ver.push_back(glm::vec3(vector));
        }
    }

    for (auto v : uvs)
    {
        uv.push_back(v);
    }

    return Object(ver, uv, "/textures/texture.jpg");
}

Object Object::getZgauche()
{
    std::vector<glm::vec3> ver;
    std::vector<glm::vec2> uv;
    for (int i = 0; i < 2; i++)
    {
        glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3(i * 2, 0, 0));
        for (auto v : vertices)
        {
            glm::vec4 vector = trans * glm::vec4(v, 1.0f);
            ver.push_back(glm::vec3(vector));
        }
    }

    for (int j = 1; j < 3; j++)
    {
        glm::mat4 trans = glm::translate(glm::mat4(1), glm::vec3(j * 2, 0, 2));
        for (auto v : vertices)
        {
            glm::vec4 vector = trans * glm::vec4(v, 1.0f);
            ver.push_back(glm::vec3(vector));
        }
    }

    for (auto v : uvs)
    {
        uv.push_back(v);
    }

    return Object(ver, uv, "/textures/texture.jpg");
}