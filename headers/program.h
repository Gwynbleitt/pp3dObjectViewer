
#ifndef PROGRAM_H
#define PROGRAM_H

#include "XClient.h"
#include "object.h"


class Program{

    char log[512];
    const char          *vshadersrc,*fshadersrc;
    unsigned int        VBO, VAO,
    /**/                vertexshader, fragmentshader, 
    /**/                shader_program;
    XEvent              event;
    GLXContext          glxc;
    float               *bgcolor;
    int                 n_fbconf;
    GLXFBConfig         *fb_conf,
                        best_fb_conf;
    GLXWindow           glx_window; 
    //static bool                glxcErrorOccurred;

    public:

    Program(int* attr_list, int eventmask, float color[3]);
    ~Program();
    
    XClient             x;
    gl_object*          object;
    
    bool SHADER_COMPILATION_CHECK (unsigned int shaderid),
         SHADER_LINK_CHECK (unsigned int shaderprogram);
    void createobject(unsigned short n, float vertex_cordinates[]),
         deleteobject(),
         drawobject(),
         Event_Loop(unsigned short n, float vertex_cordinates[]),
         redraw();
     //static int glxcErrorHandler(Display* dpy, XErrorEvent *e);
  
};

#endif