#include "program.h"
#include "glm_transform.hpp"

void Program::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action==1) switch(key){
        case GLFW_KEY_ESCAPE:
        case GLFW_KEY_Q:
            exit(EXIT_FAILURE);
            break;
        default: break;
    }
}

void Program::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    printf("framebuffer callback\n");
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
    
    glfwSetKeyCallback(win, key_callback);
    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        delete this;
        printf("failed to load GLAD\n");
    }

    cam1 = new camera({0.f,0.f,0.f},{0.f,0.f,0.f});

    translation = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);
    view_matrix = glm::mat4(1.0f);
    projection_matrix = glm::mat4(1.0f);
    transform_matrix = glm::mat4(1.0f);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 3*sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    n_vertices = indices_size/sizeof(int);

    glEnable(GL_DEPTH_TEST);

    // projection matrix
    glfwGetFramebufferSize(win, &fbwidth, &fbheight);
    projection_matrix = glm::proj_matrix_my(projection_matrix, 90, fbwidth / (float) fbheight , 0.1f, 2.f);
    //projection_matrix[2][3] = -1.0f;
    glm::print_matrix<glm::mat4>(projection_matrix,4);
    

}

void Program::drawmesh(glm::vec3 translate, glm::vec3 rotate){
    glUseProgram(shader_object -> shader_program);
    glBindVertexArray(VAO);
    glfwGetFramebufferSize(win, &fbwidth, &fbheight);

    //transform_matrix =  cam1->translate(transform_matrix, translate);
    cam1->pos = glm::vec3(cos(glfwGetTime()) * 1.f, 0.0f, sin(glfwGetTime()) * 1.f);
    view_matrix = cam1->lookat(view_matrix);
    projection_matrix = glm::proj_matrix_my(projection_matrix, 90, fbwidth / (float) fbheight , -0.5f, 0.5f);

    std::cout << "------------------\n";
    glm::print_matrix<glm::mat4>(view_matrix,4); 
    
    glUniformMatrix4fv(glGetUniformLocation(shader_object -> shader_program, "transform"), 1, false, glm::value_ptr(transform_matrix));
    glUniformMatrix4fv(glGetUniformLocation(shader_object -> shader_program, "projection"), 1, false, glm::value_ptr(projection_matrix));
    glUniformMatrix4fv(glGetUniformLocation(shader_object -> shader_program, "view"), 1, false, glm::value_ptr(view_matrix));
    glDrawElements(GL_TRIANGLES,n_vertices,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void Program::redraw(){
    //glClearColor(0.0f,0.0f,0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}


