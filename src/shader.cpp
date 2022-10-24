#include "shader.h"

std::string shader::read_shader(std::string path){
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

bool shader::SHADER_ERROR_CHECK(unsigned int id, bool type){
    int success;

    if(type) glGetProgramiv(id, GL_LINK_STATUS, &success);
    else     glGetShaderiv(id, GL_COMPILE_STATUS, &success);        
    
    if(!success) {
        glGetShaderInfoLog(id, 512, NULL, log);
        if(type) printf("SHADER PROGRAM LINKING ERROR\n%s\n",log);
        else     printf("SHADER COMPILATION ERROR\n%s\n",log);
    }
    return success ? 1 : 0;
}

shader::shader(std::string vs_path, std::string fs_path){

    std::string tmp = read_shader(vs_path);
    const char* shadersrc = tmp.c_str();

    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader, 1, &shadersrc, NULL);
    glCompileShader(vertexshader);

    tmp = read_shader(fs_path);
    shadersrc = tmp.c_str();

    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader, 1, &shadersrc, NULL);
    glCompileShader(fragmentshader);

    if(!(SHADER_ERROR_CHECK(vertexshader,SHADER)&&SHADER_ERROR_CHECK(fragmentshader,SHADER))) exit(EXIT_FAILURE);

    std::cout << "SHADERS_COMPILED\n";

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertexshader);
    glAttachShader(shader_program, fragmentshader);
    glLinkProgram(shader_program);

    if(!SHADER_ERROR_CHECK(shader_program, SHADER_PROGRAM) ) exit(EXIT_FAILURE);
    printf("SHADER_PROGRAM_LINKED\n");

    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);

}

shader::~shader(){
    glDeleteProgram(shader_program);
}