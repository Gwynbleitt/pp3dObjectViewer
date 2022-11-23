#include "program.h"
#include "obj_loader.h"

int main(int argc, char* argv[]){
    
    if(glfwInit()){

        obj_loader* loader = new obj_loader;

        loader->path = "../models/suzanne.obj";
        loader->load();

        Program* program = new Program();

        program -> createmesh(loader->vertex_n * sizeof(float),loader->index_n * sizeof(unsigned int),loader -> vertex, loader-> index);

        delete loader;

        program -> Event_Loop(0.05f);

        delete program;
        
        return EXIT_SUCCESS;
    
    } else {

        printf("Failed to Initialize GLFW");
        return EXIT_FAILURE;

    } 
}

