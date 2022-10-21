#define GL_GLEXT_PROTOTYPES
#include "program.h"


int main(int argc, char* argv[]){
    
    if(glfwInit()){

        float vertex_cord_arr[]  = { 
            -0.5f, -0.5f, 0.0f, 
            0.5f, -0.5f, 0.0f, 
            0.0f,  0.5f, 0.0f
        },
        
        color[3] = {0.0f,0.5f,1.0f};

        Program* program = new Program(color, 0);

        program -> createobject(3, vertex_cord_arr);
        program -> Event_Loop();
        
        return EXIT_SUCCESS;
    
    } else {

        printf("Failed to Initialize GLFW");
        return EXIT_FAILURE;

    } 
}

