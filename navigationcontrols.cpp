#include "navigationcontrols.h"
#include "imgui/imgui.h"

NavigationControls::NavigationControls(GLFWwindow *window, Camera *camera):Controls(window, camera), lastPosCursor(-1,-1)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    mouseSpeed = 0.02;
    counter = 0.0;
    entier = 1.0;
}

void NavigationControls::update(float deltaTime, Shader *shader)
{

    // On teste d'abord si on est sur la fenêtre imgui ou pas
    if (/*!io.WantCaptureMouse*/true){

        // left object (press K)
        if (glfwGetKey(m_Window, GLFW_KEY_K ) == GLFW_PRESS){
            m_Object->moveLeft();
        }

        // right object (press M)
        if (glfwGetKey(m_Window, GLFW_KEY_M ) == GLFW_PRESS){
            m_Object->moveRight();
        }

        // rotate object (press O)
        if (glfwGetKey(m_Window, GLFW_KEY_O ) == GLFW_PRESS){
            m_Object->rotation();
        }

        //Descente de la pièce à intervalle régulier -> chaque seconde
        counter += deltaTime;

        if (counter >= entier)
        {
            m_Object->descend();
            entier += 1.0; //changer lorsque le palier valant une seconde a été dépassé
        }
    }

}
