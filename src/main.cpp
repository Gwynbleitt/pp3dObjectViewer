#include "program.h"


int main(int argc, char* argv[]){
    
    if(glfwInit()){
        
        float vertex_cord_arr[]  = {
            //VERTEX CORDS          //VERTEX COLOR 
            -0.5f, -0.5f, 0.0f,     1.0f, 0.0f,1.0f,
            0.5f,  -0.5f, 0.0f,     0.0f, 1.0f,0.0f,
            0.5f,  0.5f, 0.0f,      0.0f, 0.0f,1.0f,
            -0.5f, 0.5f, 0.0f,      0.0f, 1.0f, 1.0f
        };
        unsigned int indeces[]={
            0,1,3,
            1,2,3
        };

        Program* program = new Program();

        program -> createmesh(sizeof(vertex_cord_arr),sizeof(indeces),vertex_cord_arr, indeces);
        program -> Event_Loop();

        delete program;
        
        return EXIT_SUCCESS;
    
    } else {

        printf("Failed to Initialize GLFW");
        return EXIT_FAILURE;

    } 
}

