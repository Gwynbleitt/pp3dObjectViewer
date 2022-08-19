
#ifndef PROGRAM_H
#define PROGRAM_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include<GL/glx.h>
#include<GL/glu.h>

#include "XClient.h"
#include "object.h"


class Program{

    public:

    Program(int* attr_list, int eventmask);
    ~Program();
    
    XClient             x;
    gl_object*          object;
    GLXContext          glxc;
    XEvent event;
    
    void createobject(int n, float vertex_cordinates[][3]);
    void deleteobject();
    void Event_Loop();
  
};

#endif