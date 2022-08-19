#include "program.h"

Program::Program(int* attr_list, int eventmask){

    x.Connect();

    x.xvinfo = glXChooseVisual(x.dpy, x.screen, attr_list);
    x.setcm();
    x.xattr.colormap = x.colormap;
    x.xattr.event_mask = eventmask ;
    x.createwindow();

    x.gc = XCreateGC(x.dpy,x.win,None,&x.gcinfo);
    x.glxc = glXCreateContext(x.dpy,x.xvinfo,NULL,1); 
    glXMakeCurrent(x.dpy, x.win, x.glxc);

    glEnable(GL_DEPTH_TEST); 
}

Program::~Program(){
    delete object;
    x.Close();
}

void Program::createobject(int n, float vertex_cordinates[][3]){
    object = new gl_object(n, vertex_cordinates);
}

void Program::deleteobject(){
    delete object;
}

void Program::Event_Loop(){

    for(;;){
        
        XNextEvent(x.dpy,&event);

        switch(event.type){
            case(Expose):
                XGetWindowAttributes(x.dpy, x.win, &x.xwinattr);
                glViewport(0, 0, x.xwinattr.width, x.xwinattr.height); 
                glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                glXSwapBuffers(x.dpy, x.win);
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
}