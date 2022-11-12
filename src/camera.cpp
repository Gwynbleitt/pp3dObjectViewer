#include "camera.h"

camera::camera(glm::vec3 view_origin, glm::vec3 cords){
    pos = cords;
    target = view_origin;
    direction = glm::normalize(target - pos);
}

glm::mat4 camera::translate(glm::mat4 transform, glm::vec3 trans_vec){
    pos[0]=trans_vec[0];
    pos[1]=trans_vec[1];
    pos[2]=trans_vec[2];
    transform[3][0] = -1*trans_vec[0];
    transform[3][1] = -1*trans_vec[1];
    transform[3][2] = -1*trans_vec[2];

    return transform;
}

glm::mat4 camera::lookat(glm::mat4 view_matrix){

    direction = glm::normalize(target - pos);
    right = glm::normalize(glm::cross(direction, glm::vec3(0.f,1.f,0.f)));
    up = glm::normalize(glm::cross(right, direction));



    view_matrix[0] = glm::vec4(right,0.f);
    view_matrix[1] = glm::vec4(up,0.f);
    view_matrix[2] = glm::vec4(direction,0.f);

    return view_matrix;
}

