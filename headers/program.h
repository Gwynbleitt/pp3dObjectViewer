
#ifndef PROGRAM_H
#define PROGRAM_H

#include "XClient.h"
#include "object.h"


class Program{

    char log[512];
    const char          *vshadersrc,*fshadersrc;
    unsigned int        vertexbuffer, 
    /**/                vertexshader, fragmentshader, 
    /**/                shader_program;
    XEvent              event;
    GLXContext          glxc;
    float*              bgcolor;

    public:

    Program(int* attr_list, int eventmask, float color[3]);
    ~Program();
    
    XClient             x;
    gl_object*          object;
    
    bool SHADER_COMPILATION_CHECK (unsigned int shaderid),
         SHADER_LINK_CHECK (unsigned int shaderprogram);
    void createobject(unsigned short n, float vertex_cordinates[][3]),
         deleteobject(),
         Event_Loop(),
         redraw();
  
};

#endif