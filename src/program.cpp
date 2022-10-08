#define GL_GLEXT_PROTOTYPES
#include "program.h"
/*
int Program::glxcErrorHandler(Display* dpy, XErrorEvent *e){
        glxcErrorOccurred = true;
        return 0;
    }
*/
Program::Program(int* attr_list, int eventmask, float color[3]){

    typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );

    vshadersrc = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    fshadersrc = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f,1.0f,1.0f,1.0f);\n"
    "}\n\0";

    x.Connect();

    fb_conf = glXChooseFBConfig(x.dpy, x.screen, attr_list, &n_fbconf);

    if(!fb_conf) {
        std::cout << "No Compatible FB Config \n";
        exit( EXIT_FAILURE );
    } else std::cout << "found fbconfig: " << n_fbconf << "\n";

    int bestfbc = 0,
        best_n_samples = 0,
        sample_buffer,
        n_samples;

    for(int i = 0; i < n_fbconf; i++){

        glXGetFBConfigAttrib(x.dpy, fb_conf[i], GLX_SAMPLE_BUFFERS, &sample_buffer);
        glXGetFBConfigAttrib(x.dpy, fb_conf[i], GLX_SAMPLES, &n_samples);

        std::cout << i << " sample buffer, "  << "sample count: "  << sample_buffer << "," << n_samples << "\n"; 

        if(sample_buffer, n_samples > best_n_samples){
            bestfbc = i;
            best_n_samples = n_samples;
        }
    }

    std::cout << "best fb_config: " << bestfbc << '\n';
    best_fb_conf = fb_conf[bestfbc];
    XFree(fb_conf);

    x.xvinfo = glXGetVisualFromFBConfig(x.dpy, best_fb_conf);
    
    x.setcm();
    x.xattr.colormap = x.colormap;
    x.xattr.event_mask = eventmask ;
    x.createwindow();
    
    int c_attr[]{
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 6,
        None
    };

    x.gc = XCreateGC(x.dpy,x.win,None,&x.gcinfo);
    glxc = glXCreateContextAttribsARB(x.dpy, best_fb_conf, 0, true, c_attr);
    //glXMakeCurrent(x.dpy, x.win, glxc);
    glx_window = glXCreateWindow(x.dpy, best_fb_conf, x.win, None);

    if( !glx_window ) {
		printf( "failed to open glx window\n" );
	}

    XMapRaised(x.dpy,x.win);
    XGetWindowAttributes(x.dpy,x.win,&x.xwinattr);
    XStoreName(x.dpy,x.win, "pp3dObjectViewer");
    
    glXMakeContextCurrent(x.dpy, glx_window, glx_window, glxc);
        

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE); 

    bgcolor = color;
}

Program::~Program(){
    delete object;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader_program);
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


void Program::createobject(unsigned short n, float vertex_cordinates[]){

    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,n*sizeof(float),vertex_cordinates,GL_STATIC_DRAW);

    object = new gl_object(n*3, vertex_cordinates);

    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader,1,&vshadersrc,NULL);
    glCompileShader(vertexshader);

    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader,1,&fshadersrc,NULL);
    glCompileShader(fragmentshader);

    if(!( SHADER_COMPILATION_CHECK(vertexshader) && SHADER_COMPILATION_CHECK(fragmentshader))) x.Close();

    std::cout << "SHADERS LOADED\n";
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertexshader);
    glAttachShader(shader_program, fragmentshader);
    glLinkProgram(shader_program);

    if(!SHADER_LINK_CHECK(shader_program)) x.Close(); 

    std::cout << "SHADER PROGRAM LINKED\n";

    /*glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);*/

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    /* PRINT VERTICIES */

    for(int i = 0; i < n; i++){
        for(int j = 0; j < 3; j++) std::cout << vertex_cordinates[(i*3)+j] << ';';
        std::cout<< '\n';
    }
}

void Program::drawobject(){
    
    glUseProgram(shader_program);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
    std::cout << "\nobject drawn\n";
}

void Program::redraw(){
   XGetWindowAttributes(x.dpy, x.win, &x.xwinattr);
   glViewport(0, 0, x.xwinattr.width, x.xwinattr.height);  
   glClearColor(bgcolor[0],bgcolor[1],bgcolor[2], 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);
   drawobject();
}

