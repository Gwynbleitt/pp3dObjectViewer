#ifndef OBJECT_H
#define OBJECT_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glu.h>

class gl_object{

    unsigned short vertex_count;

    public:

    /* x,y,z */
    float** vertex_global_cords,
    * origin_cords;

    gl_object(unsigned short n, float arr[][3]);

    ~gl_object();

};

#endif