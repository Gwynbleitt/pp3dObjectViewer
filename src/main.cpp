#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "XClient.h"

using XFunctions::XClient;

XClient x;
GC gc;
XGCValues gcinfo;

int main(){
    x.Connect();
    x.setcm(TrueColor);

    /* verify depth */

    std::cout << DefaultDepth(x.dpy,x.screen) << '\n';

    /* Graphics Context */

    gcinfo.foreground = x.RGBtoPixel_24(200,50,200);
    gcinfo.line_width = 10;

    gc = XCreateGC(x.dpy,x.win,GCForeground | GCLineWidth,&gcinfo);

    /* Event Handling Loop */

    XEvent event;

    for(;;){
        XNextEvent(x.dpy,&event);

        switch(event.type){
            case(Expose):
            XDrawLine(x.dpy,x.win,gc,0,0,100,100);
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

