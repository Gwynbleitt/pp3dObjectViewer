#include "program.h"

int main(int argc, char* argv[]){

    int attr_list[] = {
        GLX_RGBA,             
        GLX_DEPTH_SIZE, 24,    
        GLX_DOUBLEBUFFER,       
        None
    };

    float vertex_cord_arr[][3]  = { 
        {0.0f,0.0f,0.0f},
        {1.0f,0.0f,0.0f},
        {1.0f,1.0f,0.0f},
        {0.0f,1.0f,0.0f} 
    };

    Program* program = new Program(attr_list, ExposureMask | KeyPressMask);

    program -> createobject(4,vertex_cord_arr);

    program -> Event_Loop();

    delete program;

    return 0;
}

