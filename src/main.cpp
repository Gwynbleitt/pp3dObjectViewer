#include "program.h"
#include "obj_loader.h"

int main(int argc, char* argv[]){
    
    if(glfwInit()){

        obj_loader* loader = new obj_loader;

        
        loader->path = "../models/suzanne.obj";
        loader->load_vert();
        loader->load_index();

        
        
        float vertex_cord_arr[] //= loader -> load_vert();

          = {
            
            //  X      Y     Z      
             0.5f,  0.5f,  0.5f, //0          3---0 
             0.5f, -0.5f,  0.5f, //1          |   |  
            -0.5f, -0.5f,  0.5f, //2          2---1 
            -0.5f,  0.5f,  0.5f,  //3           

             0.5f,  0.5f, -0.5f, //4          7---4 
             0.5f, -0.5f, -0.5f, //5          |   |  
            -0.5f, -0.5f, -0.5f, //6          6---5 
            -0.5f,  0.5f, -0.5f  //7           

        }; 

        
        unsigned int indeces[] //= loader->load_index();
        
        ={

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
        
        delete loader;

        Program* program = new Program();

        program -> createmesh(sizeof(vertex_cord_arr),sizeof(indeces),vertex_cord_arr, indeces);
        program -> Event_Loop(0.05f);

        delete program;
        
        return EXIT_SUCCESS;
    
    } else {

        printf("Failed to Initialize GLFW");
        return EXIT_FAILURE;

    } 
}

