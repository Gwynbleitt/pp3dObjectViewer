#define GL_GLEXT_PROTOTYPES
#include "program.h"

void Program::Event_Loop(){

    while(!glfwWindowShouldClose(win)){

        redraw();

        glfwSwapBuffers(win);
        glfwPollEvents();
    }
}