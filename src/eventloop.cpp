#define GL_GLEXT_PROTOTYPES
#include "program.h"

void Program::Event_Loop(float speed){

    while(!glfwWindowShouldClose(win)){

        if(glfwGetKey(win, GLFW_KEY_A)) translation[0]-=speed;
        if(glfwGetKey(win, GLFW_KEY_W)) translation[2]+=speed;   
        if(glfwGetKey(win, GLFW_KEY_S)) translation[2]-=speed;
        if(glfwGetKey(win, GLFW_KEY_D)) translation[0]+=speed;

        else if(glfwGetKey(win, GLFW_KEY_E)) {
            rotation[2]+=PI/180.0;
            rotation[1]+=PI/180.0;
            rotation[0]+=PI/180.0;
        }
        redraw();
        drawmesh(translation, rotation);

        glfwSwapBuffers(win);
        glfwPollEvents();
    }
}