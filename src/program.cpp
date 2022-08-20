#define GL_GLEXT_PROTOTYPES
#include "program.h"

Program::Program(int* attr_list, int eventmask, float color[3]){

    vshadersrc = "#version 330 core\n"
        "layout (location=0) in vec3 aPos;\n"
        "void main(){\n"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    fshadersrc = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main(){\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);\n"
        "}\0";

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

    bgcolor = color;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
    shader_program = glCreateProgram();
}

Program::~Program(){
    delete object;
    x.Close();
}

bool Program::SHADER_COMPILATION_CHECK(unsigned int shaderid){
    int success;
    glGetShaderiv(shaderid, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shaderid, 512, NULL, log);
        std::cout << "SHADER COMPILATION ERROR\n" << log;
    }
    return success ? 1 : 0;
}

bool Program::SHADER_LINK_CHECK(unsigned int shaderprogram){
    int success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shaderprogram, 512, NULL, log);
        std::cout << "SHADER PROGRAM LINKING ERROR\n" << log;
    }
    return success ? 1 : 0;
}


void Program::createobject(unsigned short n, float vertex_cordinates[][3]){
    object = new gl_object(n, vertex_cordinates);
    glBufferData(GL_ARRAY_BUFFER,n*sizeof(float),vertex_cordinates,GL_DYNAMIC_DRAW /*GL_STATIC_DRAW ? (if no changes to mesh)*/);

    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexshader,1,&vshadersrc,NULL);
    glShaderSource(fragmentshader,1,&fshadersrc,NULL);

    glCompileShader(vertexshader);
    glCompileShader(fragmentshader);

    if(!( SHADER_COMPILATION_CHECK(vertexshader) && SHADER_COMPILATION_CHECK(fragmentshader))) x.Close();

    std::cout << "SHADERS LOADED\n";

    glAttachShader(shader_program, vertexshader);
    glAttachShader(shader_program, fragmentshader);
    glLinkProgram(shader_program);

    if(!SHADER_LINK_CHECK(shader_program)) x.Close(); 

    std::cout << "SHADER PROGRAM LINKED\n";
    glUseProgram(shader_program);

    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);

    glVertexAttribPointer(0,3,GL_FLOAT,0,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
}

void Program::redraw(){
   XGetWindowAttributes(x.dpy, x.win, &x.xwinattr);
   glViewport(0, 0, x.xwinattr.width, x.xwinattr.height);  
   glClearColor(*bgcolor,*(bgcolor+1),*(bgcolor+2), 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);
}

