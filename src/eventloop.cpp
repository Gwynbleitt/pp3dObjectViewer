#define GL_GLEXT_PROTOTYPES
#include "program.h"


void Program::Event_Loop(float speed){

    while(!glfwWindowShouldClose(win)){

        if(glfwGetKey(win, GLFW_KEY_A)) translation.x+=speed;
        if(glfwGetKey(win, GLFW_KEY_W)) translation.z-=speed;   
        if(glfwGetKey(win, GLFW_KEY_S)) translation.z+=speed;
        if(glfwGetKey(win, GLFW_KEY_D)) translation.x-=speed;

        if(glfwGetKey(win, GLFW_KEY_RIGHT)) rotation.x -= PI/90;
        if(glfwGetKey(win, GLFW_KEY_LEFT)) rotation.x += PI/90;
        if(glfwGetKey(win, GLFW_KEY_UP)) rotation.y -= PI/90;
        if(glfwGetKey(win, GLFW_KEY_DOWN)) rotation.y += PI/90;

        redraw();
        drawmesh(translation, rotation);

        glfwSwapBuffers(win);
        glfwPollEvents();
    }
}