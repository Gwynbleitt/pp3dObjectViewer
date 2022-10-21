#include "object.h"

gl_object::gl_object(unsigned short n, float arr[]){
    vertex_count = n;
    vertex_global_cords = new float [n];
    vertex_global_cords = arr;
}

gl_object::~gl_object(){delete [] vertex_global_cords;}