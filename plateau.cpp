//
// Created by vivie on 15/11/2025.
//

#include "plateau.h"


void Plateau::build(Object o, Camera cam, Shader shader, Renderer renderer, VertexArray va)
{
    glm::mat4 m;
    glm::mat4 v;
    glm::mat4 p;
    glm::mat4 mvp;
    //construction du plateau
    for (int i = 0; i <= 11; i++) {
        cam.computeMatrices(600, 600);
        o.position.x=-2+2*i;
        m = o.getModelMatrix();
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();

        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);
        renderer.Clear();
        renderer.Draw(va, o, shader);
    }
    for (int j = 1; j <= 12; j++) {
        o.position.x=-2;
        o.position.z=2*j;
        cam.computeMatrices(600, 600);
        m = o.getModelMatrix();
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();

        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);
        renderer.Clear();
        renderer.Draw(va, o, shader);
    }
    for (int k = 1; k <= 12; k++) {
        o.position.x=22;
        o.position.z=2*k;
        cam.computeMatrices(600, 600);
        m = o.getModelMatrix();
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();

        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);
        renderer.Clear();
        renderer.Draw(va, o, shader);
    }
}