#define GL_GLEXT_PROTOTYPES
#include "program.h"


void Program::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    printf("framebuffer callback\n");
}

void Program::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action==1) switch(key){
        case GLFW_KEY_ESCAPE:
        case GLFW_KEY_Q:
            exit(EXIT_FAILURE);
            break;
        default: printf("pressed:%i\n",key);break;
    }
}

std::string Program::read_shader(std::string path){
    std::string line, tmp = "";
    std::ifstream file;
    file.open( path );
    if(file.is_open()){
        while(getline(file,line)){
            tmp.append(line);
            tmp.append("\n");
        }
       file.close(); 
    } else printf("FAILED TO READ SHADER\n");
    return tmp;
}

Program::Program(float color[3], bool FULLSCREEN){

    monitor = glfwGetPrimaryMonitor();

    if(!monitor) printf("NO MONITOR FOUND");

    vid_mode = glfwGetVideoMode( monitor );

    /*glfwWindowHint(GLFW_RED_BITS, vid_mode -> redBits);
    glfwWindowHint(GLFW_GREEN_BITS, vid_mode -> greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, vid_mode -> blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, vid_mode -> refreshRate);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);*/
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    
    if( FULLSCREEN ) win = glfwCreateWindow(vid_mode -> width, vid_mode -> height, "pp-3D-object-viewer", monitor , NULL);
    else win = glfwCreateWindow(vid_mode -> width/2, vid_mode -> height/2, "pp-3D-object-viewer", NULL , NULL);

    if(!win) printf("FAILED TO CREATE WINDOW");

    glfwMakeContextCurrent( win );
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        glfwSetWindowShouldClose(win, 1);
        printf("failed to load GLAD\n");
    }

    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
    glfwSetKeyCallback(win, key_callback);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE); 

    bgcolor = color;
    
}

Program::~Program(){
    delete object;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader_program);
    glfwDestroyWindow(win);
    glfwTerminate();
}


bool Program::SHADER_COMPILATION_CHECK(unsigned int shaderid){
    int success;
    glGetShaderiv(shaderid, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shaderid, 512, NULL, log);
        printf("SHADER COMPILATION ERROR\n%s\n",log);
    }
    return success ? 1 : 0;
}

bool Program::SHADER_LINK_CHECK(unsigned int shaderprogram){
    int success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shaderprogram, 512, NULL, log);
        printf("SHADER PROGRAM LINKING ERROR\n%s\n",log);
    }
    return success ? 1 : 0;
}


void Program::createobject(unsigned short n, float vertex_cordinates[]){

    object = new gl_object(n*3, vertex_cordinates);

    std::string tmp = read_shader("../shaders/shader.vert");
    const char* shadersrc = tmp.c_str();

    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader,1,&shadersrc,NULL);
    glCompileShader(vertexshader);

    tmp = read_shader("../shaders/shader.frag");
    shadersrc = tmp.c_str();

    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader,1,&shadersrc,NULL);
    glCompileShader(fragmentshader);

    if(!( SHADER_COMPILATION_CHECK(vertexshader) && SHADER_COMPILATION_CHECK(fragmentshader))) delete this;

    printf("SHADERS LOADED\n");
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertexshader);
    glAttachShader(shader_program, fragmentshader);
    glLinkProgram(shader_program);

    if(!SHADER_LINK_CHECK(shader_program) ) delete this;
    printf("SHADER PROGRAM LINKED\n");

    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, n*sizeof(float), vertex_cordinates, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, n*sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    
   

    
}

void Program::drawobject(){
    glUseProgram(shader_program);
    glBindVertexArray(VAO); 
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Program::redraw(){

    glClearColor(bgcolor[0],bgcolor[1],bgcolor[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawobject();
}


