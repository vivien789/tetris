#ifndef OBJECT_H
#define OBJECT_H
#define GLM_ENABLE_EXPERIMENTAL

#include <string>

#include "shader.h"
#include "glm/glm.hpp"

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "texture.h"
#include "uvbuffer.h"
#include "glm/vec3.hpp"

class Object
{
public:
    Object(std::vector< glm::vec3 > vertices, std::vector< glm::vec2 > uvs, std::string texturePath);
    ~Object();
    void Bind() const;
    void Unbind() const;
    void Draw() const;
    void descend();
    void rotation();
    void moveLeft();
    void moveRight();
    glm::vec3 getPosition() const;
    glm::vec3 position;
    glm::vec3 rotationAngles;
    std::vector<glm::vec3> vertices;
    std::vector< glm::vec2 > uvs;
    bool toDelete;
    glm::mat4 getModelMatrix();

    Object getTquadri();
    Object getBaton();
    Object getCarre();
    Object getLgauche();
    Object getLdroite();
    Object getZgauche();
    Object getZdroite();

private:
    VertexBuffer *m_vb;
    UVBuffer *m_uvsb;
    Texture *m_texture;

};

#endif // OBJECT_H
