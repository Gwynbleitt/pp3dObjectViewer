#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>

#include "XClient.h"

using namespace XFunctions;

void XClient::Connect(){

    dpy = XOpenDisplay(NULL);

    if(dpy){
        screen = DefaultScreen(dpy);
        root = DefaultRootWindow(dpy);
        win = XCreateSimpleWindow(dpy, root,0,0,DisplayWidth(dpy,screen),DisplayHeight(dpy,screen),0,0,0);
        XMapRaised(dpy,win);
        XSelectInput(dpy,win,ExposureMask | KeyPressMask);
        XGetWindowAttributes(dpy,win,&xattr);
        XFlush(dpy);
    }

    else std::cout << "Failed to connect with XServer" << '\n';
}

void XClient::setcm(int c_class){

    Visual* tmp;
    int vinfo_return;
    XVisualInfo xvinfo;
    xvinfo.c_class = c_class;

    tmp = (XGetVisualInfo(dpy,VisualClassMask,&xvinfo,&vinfo_return))->visual;

    colormap = XCreateColormap(dpy, win, tmp, AllocNone); 
}

/* takes rgb values from 0 to 255 and converts it to 24 bit pixel value */
unsigned long XClient::RGBtoPixel_24(int R, int G, int B){
    return (65536*R) + (256*G) + B;
}

void XClient::Close(){
    XFreeColormap(dpy, colormap);
    XCloseDisplay(dpy);
    exit(1);
}
