#define GL_GLEXT_PROTOTYPES
#include "program.h"


void Program::Event_Loop(float speed){

    while(!glfwWindowShouldClose(win)){

        if(glfwGetKey(win, GLFW_KEY_A)) translation += speed * glm::normalize(glm::cross(glm::vec3(direction2d.x,0.f,direction2d.y),glm::vec3(0.f,1.f,0.f)));
        if(glfwGetKey(win, GLFW_KEY_W)) translation += speed * glm::vec3(direction2d.x,0.f,direction2d.y);   
        if(glfwGetKey(win, GLFW_KEY_S)) translation -= speed * glm::vec3(direction2d.x,0.f,direction2d.y);
        if(glfwGetKey(win, GLFW_KEY_D)) translation -= speed * glm::normalize(glm::cross(glm::vec3(direction2d.x,0.f,direction2d.y),glm::vec3(0.f,1.f,0.f)));
        if(glfwGetKey(win, GLFW_KEY_LEFT_SHIFT)) translation.y += speed;
        if(glfwGetKey(win, GLFW_KEY_SPACE)) translation.y -= speed;

        if(glfwGetKey(win, GLFW_KEY_RIGHT)) rotation.x -= PI/90;
        if(glfwGetKey(win, GLFW_KEY_LEFT)) rotation.x += PI/90;
        if(glfwGetKey(win, GLFW_KEY_UP)) rotation.y -= PI/90;
        if(glfwGetKey(win, GLFW_KEY_DOWN)) rotation.y += PI/90;

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        drawmesh(translation, rotation);

        glfwSwapBuffers(win);
        glfwPollEvents();
    }
}