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
    },

    color[3] = {0.0f,0.5f,1.0f};

    Program* program = new Program(attr_list, ExposureMask | KeyPressMask, color);

    int maj, min;
    glXQueryVersion(program->x.dpy,&maj,&min);
    std::cout << "OpenGL version:\n  Maj:" << maj << "\n  Min:" << min << "\n\n";

    program -> createobject(4,vertex_cord_arr);
    program -> Event_Loop();

    delete program;

    return 0;
}

