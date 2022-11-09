#include "program.h"

int main(int argc, char* argv[]){
    
    if(glfwInit()){
        
        float vertex_cord_arr[]  = {
            /* VERTEX CORDS
              X      Y     Z */       
             0.5f,  0.5f,  0.5f, //0          3---0 
             0.5f, -0.5f,  0.5f, //1          |   |  
            -0.5f, -0.5f,  0.5f, //2          2---1 
            -0.5f,  0.5f,  0.5f,  //3           

             0.5f,  0.5f, -0.5f, //4          7---4 
             0.5f, -0.5f, -0.5f, //5          |   |  
            -0.5f, -0.5f, -0.5f, //6          6---5 
            -0.5f,  0.5f, -0.5f  //7           

        };
        unsigned int indeces[]={

            0,1,3,
            1,2,3,

            4,5,7,
            5,6,7,

            0,1,5,
            4,0,5,

            6,7,2,
            3,2,7,

            3,0,7,
            7,4,0,

            6,5,2,
            2,1,5
        };

        Program* program = new Program();

        program -> createmesh(sizeof(vertex_cord_arr),sizeof(indeces),vertex_cord_arr, indeces);
        program -> Event_Loop(0.01f);

        delete program;
        
        return EXIT_SUCCESS;
    
    } else {

        printf("Failed to Initialize GLFW");
        return EXIT_FAILURE;

    } 
}

