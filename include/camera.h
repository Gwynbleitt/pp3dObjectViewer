#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include  "glad/glad.h"

class camera{

    public:

    glm::vec3 r;    //right
    glm::vec3 u;    //up

    glm::mat4 translate(glm::mat4 transform, glm::vec3 trans_vec);
    glm::mat4 lookat(glm::mat4 view_matrix,glm::vec3 d, glm::vec3 t);
    
    camera(glm::vec3 cords, unsigned int shader_program, const char* var_name);
    ~camera();
    
};

#endif