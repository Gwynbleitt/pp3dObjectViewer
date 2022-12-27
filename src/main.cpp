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

        loader->path = "../models/car.obj";
        loader->load();

        float* vertex_attr = merge_arr<float>(loader->vertex, loader->normals, loader->vertex_n*2, 3);

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
