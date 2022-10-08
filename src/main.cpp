#define GL_GLEXT_PROTOTYPES
#include "program.h"

int main(int argc, char* argv[]){

    int attr_list[] = {
        GLX_X_RENDERABLE    , True,
        GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
        GLX_RENDER_TYPE     , GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
        GLX_RED_SIZE        , 8,
        GLX_GREEN_SIZE      , 8,
        GLX_BLUE_SIZE       , 8,
        GLX_ALPHA_SIZE      , 8,
        GLX_DEPTH_SIZE      , 24,
        GLX_STENCIL_SIZE    , 8,
        GLX_DOUBLEBUFFER    , True,

        None
    };

    float vertex_cord_arr[]  = { 
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    },

    color[3] = {0.0f,0.5f,1.0f};

    Program* program = new Program(attr_list, ExposureMask | KeyPressMask, color);

    int major = 0, minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    printf("OpenGL context created.\nVersion %d.%d\nVendor %s\nRenderer %s\n",
           major, minor,
           glGetString(GL_VENDOR),
           glGetString(GL_RENDERER));
    program -> Event_Loop(3,vertex_cord_arr);

    delete program;

    return 0;
}

