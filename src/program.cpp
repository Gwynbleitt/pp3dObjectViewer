#include "program.h"
#include <glm_transform.hpp>


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

    translation = glm::vec3(0.0f);
    rotation = glm::vec2(0.5*PI,0.f);
    view_matrix = glm::mat4(1.0f);
    projection_matrix = glm::mat4(1.0f);
}

Program::~Program(){

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete shader_object;
    glfwDestroyWindow(win);
    glfwTerminate();
}


void Program::createmesh(int vertices_size, int indices_size, float* vertex_cordinates, unsigned int* indices){

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

    cam1 = new camera(glm::vec3(0.f,0.f,-10.f),shader_object->shader_program, "camera_pos");

    // projection matrix
    glfwGetFramebufferSize(win, &fbwidth, &fbheight);
    projection_matrix = glm::proj_matrix_my(projection_matrix, 90.f, fbwidth / (float) fbheight , 0.1f, 2.f);
}

void Program::drawmesh(glm::vec3 translate, glm::vec2 rotate){
    double cx, cy;

    glUseProgram(shader_object -> shader_program);
    
    glfwGetFramebufferSize(win, &fbwidth, &fbheight);
    glfwGetCursorPos(win, &cx, &cy);

    cx -= fbwidth/2;
    cy -= fbheight/2;

    cx/=-180;
    cy/=180;

    cx+=PI/2;

    direction = glm::rotate2<glm::vec3>(direction, cx, cy);
    direction2d = glm::rotate1<glm::vec2>(direction2d, cx);

    view_matrix = cam1->lookat(view_matrix,direction,translate);
    projection_matrix = glm::proj_matrix_my(projection_matrix, 45, fbwidth / (float) fbheight , 1.f, 100.0f);

    glUniformMatrix4fv(glGetUniformLocation(shader_object -> shader_program, "projection"), 1, false, glm::value_ptr(projection_matrix));
    glUniformMatrix4fv(glGetUniformLocation(shader_object -> shader_program, "view"), 1, false, glm::value_ptr(view_matrix));
    
    glDrawElements(GL_TRIANGLES,n_vertices,GL_UNSIGNED_INT,0);
}



