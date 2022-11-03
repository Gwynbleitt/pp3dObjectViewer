#define GL_GLEXT_PROTOTYPES
#include "program.h"

void Program::Event_Loop(float speed){

    while(!glfwWindowShouldClose(win)){

        if(glfwGetKey(win, GLFW_KEY_A)) x-=speed;
        if(glfwGetKey(win, GLFW_KEY_W)) y+=speed;   
        if(glfwGetKey(win, GLFW_KEY_S)) y-=speed;
        if(glfwGetKey(win, GLFW_KEY_D)) x+=speed;

        else if(glfwGetKey(win, GLFW_KEY_E)) angle++;

        redraw();
        drawmesh(x,y,z, angle);

        glfwSwapBuffers(win);
        glfwPollEvents();
    }
}