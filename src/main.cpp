#include <iostream>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "XClient.h"

using XFunctions::XClient;

XClient     x;
XGCValues   gcinfo;

int main(){

    x.Connect();

    int attrib_list[] = {
        GLX_RGBA,
        GLX_DEPTH_SIZE, 24,
        GLX_DOUBLEBUFFER, None
    };

    x.xvinfo = glXChooseVisual(x.dpy, x.screen, attrib_list);

    x.setcm();

    x.xattr.colormap = x.colormap;
    x.xattr.event_mask = ExposureMask | KeyPressMask ;

    x.createwindow();
 
    /* Graphics Context */

    gcinfo.foreground = x.RGBtoPixel_24(200,50,200);
    gcinfo.line_width = 10;

    x.gc = XCreateGC(x.dpy,x.win,GCForeground | GCLineWidth,&gcinfo);

    /* Event Handling Loop */

    XEvent event;

    for(;;){
        
        XNextEvent(x.dpy,&event);

        switch(event.type){
            case(Expose):
            XDrawLine(x.dpy,x.win,x.gc,0,0,100,100);
            break;
            case(KeyPress):
                std::cout << event.xkey.keycode << '\n';
                switch(event.xkey.keycode){
                    /*Q or ESC close window*/
                    case(24):case(9): x.Close();
                    default:break;
                }
                break;

            default:break;         
        }
    }
    
    return 0;
}

