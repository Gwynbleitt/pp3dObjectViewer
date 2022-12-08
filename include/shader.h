#ifndef SHADER_H
#define SHADER_H

#define SHADER 0
#define SHADER_PROGRAM 1
#define GL_GLEXT_PROTOTYPES

#include  "glad/glad.h"
#include  <GLFW/glfw3.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <cstring>
#include  <iostream>
#include  <fstream>

class shader{

    bool  SHADER_ERROR_CHECK (unsigned int shaderid, bool type);
    std::string read_shader(std::string path);

    char log[512];

    public:

    unsigned int shader_program, vertexshader, fragmentshader;

    shader(std::string vs_path, std::string fs_path);
    ~shader();

};

#endif