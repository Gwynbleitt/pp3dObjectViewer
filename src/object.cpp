#include "object.h"

gl_object::gl_object(unsigned short n, float arr[][3]){

    vertex_count = n;
    vertex_global_cords = new float *[n];

    for(int i = 0; i < n; i++){
        vertex_global_cords[i] = new float [3];
        vertex_global_cords[i][0] = **(arr+i);
        vertex_global_cords[i][1] = **(arr+i);
        vertex_global_cords[i][2] = *(*(arr+i)+2);
    }
}

gl_object::~gl_object(){
    for(int i = 0; i < vertex_count; i++) delete [] *(vertex_global_cords+i);
    delete [] vertex_global_cords;
}