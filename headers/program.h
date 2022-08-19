
#ifndef PROGRAM_H
#define PROGRAM_H

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