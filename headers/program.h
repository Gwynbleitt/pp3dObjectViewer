#ifndef PROGRAM_H
#define PROGRAM_H

#include  "glad/glad.h"
#include  <GLFW/glfw3.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <fstream>
#include  <iostream>
#include  "object.h"
#include  <cstring>

class Program{

    private: 

    char log[512];
    
    unsigned int        VBO, VAO,
    /**/                vertexshader, fragmentshader, 
    /**/                shader_program;
    float               *bgcolor;
    GLFWwindow          *win;
    GLFWmonitor         *monitor;
    const GLFWvidmode   *vid_mode;

    public:

    Program(float color[3], bool FULLSCREEN);
    ~Program();

    gl_object*          object;
    
    bool  SHADER_COMPILATION_CHECK (unsigned int shaderid),
          SHADER_LINK_CHECK (unsigned int shaderprogram);
    void  createobject(unsigned short n, float vertex_cordinates[]),
          deleteobject(),
          drawobject(),
          Event_Loop(),
          redraw();
    std::string read_shader(std::string path);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height),
                key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  
};

#endif