#include "program.h"
#include "obj_loader.h"

int main(int argc, char* argv[]){
    
    if(glfwInit()){

        obj_loader* loader = new obj_loader;

        loader->path = "../models/suzanne.obj";
        loader->load();

        float vertex_attr [loader->vertex_n*2];

        int i_v = 0;
        int i_n = 0;

        bool vorn = 1; // 1 -> vertex; 0 -> normal

        for(int i = 0; i < loader->vertex_n*2; i++ ){

            if(!(i%3)) vorn = abs(vorn-1);

            if(vorn) vertex_attr[i] = loader->vertex[i-((i-(i%3))/2)];
            else     vertex_attr[i] = loader->normals[i-(((i+3)-(i%3))/2)];
            
        }

  

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

