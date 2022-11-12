#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class camera{

    public:

    glm::vec3 target;
    glm::vec3 pos;

    glm::vec3 right;     //x
    glm::vec3 direction; //y
    glm::vec3 up;        //z

    glm::mat4 translate(glm::mat4 transform, glm::vec3 trans_vec);
    glm::mat4 lookat(glm::mat4 view_matrix);
    
    camera(glm::vec3 view_origin, glm::vec3 cords);
    ~camera();
    
};

#endif