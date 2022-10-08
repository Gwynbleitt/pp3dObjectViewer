
#ifndef XCLIENT_H
#define XCLIENT_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <iostream>



class XClient{
    public:
    
    /* X Varibles */

    Display*                dpy;
    int                     screen;
    Window                  win, root;
    Colormap                colormap;
    XSetWindowAttributes    xattr;
    XWindowAttributes       xwinattr;
    GC                      gc;
    XVisualInfo*            xvinfo;
    XGCValues               gcinfo;


    /* main methods */

    void Connect();
    void createwindow();
    void Close();
    void setcm(); /*set colormap based on visual*/


    /* misc */

    unsigned long RGBtoPixel_24(int R, int G, int B); 
};


#endif