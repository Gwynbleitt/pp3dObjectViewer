#ifndef OBJECT_H
#define OBJECT_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glu.h>

class gl_object{

    /* x,y,z */

    float** vertex_global_cords,
    vertex_count;

    public:

    gl_object(unsigned short n, float arr[][3]);

    ~gl_object();

};

#endif