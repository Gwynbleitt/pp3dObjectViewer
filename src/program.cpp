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
        default: break;
    }
}

Program::Program(){

    monitor = glfwGetPrimaryMonitor();
    if(!monitor) printf("NO MONITOR FOUND");
    vid_mode = glfwGetVideoMode( monitor );

    glfwWindowHint(GLFW_RED_BITS, vid_mode -> redBits);
    glfwWindowHint(GLFW_GREEN_BITS, vid_mode -> greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, vid_mode -> blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, vid_mode -> refreshRate);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    win = glfwCreateWindow(vid_mode -> width/2, vid_mode -> height/2, "pp-3D-object-viewer", NULL, NULL);
    
    if(!win) printf("FAILED TO CREATE WINDOW");

    glfwMakeContextCurrent( win );
    
    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
    glfwSetKeyCallback(win, key_callback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        delete this;
        printf("failed to load GLAD\n");
    }
    x,y,z = 0.0f;
    transform = glm::mat4(1.0f);

    std::cout << "matrix:\n";
    glm::print_matrix<glm::mat4>(transform,4);
}

Program::~Program(){

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete shader_object;
    glfwDestroyWindow(win);
    glfwTerminate();
}


void Program::createmesh(int vertices_size, int indices_size, float vertex_cordinates[], unsigned int indices[]){

    shader_object = new shader("../shaders/shader.vert","../shaders/shader.frag");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertex_cordinates, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);
    //position attribute 
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 6*sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);
    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Program::drawmesh(float deltax, float deltay, float deltaz, int delta_angle){
    glUseProgram(shader_object -> shader_program);
    glBindVertexArray(VAO);

    transform = glm::translate<glm::mat4>(transform,4, deltax, deltay, deltaz);
    transform = glm::rotate<glm::mat4>(transform,4,rotate_axis,delta_angle);

    glUniformMatrix4fv(glGetUniformLocation(shader_object -> shader_program, "transform"), 1, false, glm::value_ptr(transform));
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void Program::redraw(){
    glClearColor(.3f,.3f,.9f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}


