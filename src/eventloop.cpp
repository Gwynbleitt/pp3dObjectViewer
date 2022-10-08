#define GL_GLEXT_PROTOTYPES
#include "program.h"

void Program::Event_Loop(unsigned short n, float vertex_cordinates[]){

    XGetWindowAttributes(x.dpy, x.win, &x.xwinattr);
    glViewport(0, 0, x.xwinattr.width, x.xwinattr.height); 

    createobject(n, vertex_cordinates);

    for(;;){
        
        XNextEvent(x.dpy,&event);

        switch(event.type){
            case(Expose):
                redraw();
                break;
            case(KeyPress):
                std::cout << event.xkey.keycode << '\n';
                switch(event.xkey.keycode){
                    /*Q or ESC close window*/
                    case(24):case(9): x.Close();
                    default:break;
                }

            default:break;         
        }
        
        glXSwapBuffers(x.dpy, x.win);
    }
}