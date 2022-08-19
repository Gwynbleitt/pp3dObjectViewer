#include "XClient.h"


void XClient::Connect(){

    dpy = XOpenDisplay(NULL);

    if(dpy){
        screen = DefaultScreen(dpy);
        root = DefaultRootWindow(dpy);
        XFlush(dpy);
    }

    else{
         std::cout << "Failed to connect with XServer" << '\n';
         exit(EXIT_FAILURE);
    }
}

void XClient::setcm(){

    colormap = XCreateColormap(dpy, root, xvinfo -> visual, AllocNone); 

    XInstallColormap(dpy,colormap);
}

void XClient::createwindow(){

    win = XCreateWindow(dpy,root,0,0,XDisplayWidth(dpy,screen),XDisplayHeight(dpy,screen),0,xvinfo->depth,InputOutput,xvinfo->visual, CWColormap | CWEventMask, &xattr);

    XMapRaised(dpy,win);
    XGetWindowAttributes(dpy,win,&xwinattr);
    XStoreName(dpy,win, "pp3dObjectViewer");
    XFlush(dpy);
}

/* takes rgb values from 0 to 255 and converts it to 24 bit pixel value */

unsigned long XClient::RGBtoPixel_24(int R, int G, int B){
    return (65536*R) + (256*G) + B;
}

void XClient::Close(){
    XFreeColormap(dpy, colormap);
    XDestroyWindow(dpy,win);
    XFreeGC(dpy,gc);
    XCloseDisplay(dpy);
    exit(EXIT_FAILURE);
}
