#include "program.h"
#include "obj_loader.h"

template <typename type>

type* merge_arr(type* arr_a, type* arr_b, int size_new, int attr_size){

    type* new_arr = new type[size_new];

    int i_a = 0;
    int i_b = 0;

    bool aorb = 0;

    for(int i = 0; i < size_new; i++)
    {
        if(i%attr_size == 0) aorb = abs(aorb-1);

        if(aorb)
        {
            new_arr[i] = arr_a[i_a];
            i_a++;
        }    
        else
        {
            new_arr[i] = arr_b[i_b];
            i_b++;
        }
    }

    return new_arr;

}

int main(int argc, char* argv[]){
    
    if(glfwInit()){

        obj_loader* loader = new obj_loader;

        loader->path = "../models/suzanne_n.obj";
        loader->load();


       /* for(int i = 0; i < loader->normal_n; i++){
            if(!(i%3)) std::cout << '\n';
            std::cout << loader->normals[i] << ' ';
        }*/

        

        float* vertex_attr = merge_arr<float>(loader->vertex, loader->normals, loader->vertex_n*2, 3);

        /*int i_v = 0;
        int i_n = 0;

        bool vorn = 1; // 1 -> vertex; 0 -> normal

        for(int i = 0; i < loader->vertex_n*2; i++ ){

           if(!(i%3)) vorn = abs(vorn-1);

           if(vorn) vertex_attr[i] = loader->vertex[i-((i-(i%3))/2)];
           else     vertex_attr[i] = loader->normals[i-(((i+3)-(i%3))/2)];
            
        } */

        /*std::cout << "TEST: " << '\n';

        for(int i = 0; i <= 5; i++){
            std::cout << vertex_attr[i] << ',';
        } 
        std::cout << '\n';
        for(int i = 6; i <= 11; i++){
            std::cout << vertex_attr[i] << ',';
        }
        std::cout << '\n'; */

        for(int i = 0; i <=5; i++){
            
            if(i%3 == 0) std::cout << '\n';
            std::cout<< vertex_attr[i] << ' ';
        }

  

        Program program;

    
        program.createmesh(loader->vertex_n * sizeof(float) * 2,loader->index_n * sizeof(unsigned int),vertex_attr, loader-> index);

        delete loader;

        program.Event_Loop(0.05f);
        
        return EXIT_SUCCESS;
    
    } else {

        printf("Failed to Initialize GLFW");
        return EXIT_FAILURE;

    } 
}

