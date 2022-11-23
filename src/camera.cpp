#include "camera.h"
#include <iostream>

camera::camera(glm::vec3 view_origin, glm::vec3 cords){
    pos = cords;
    target = view_origin;
}

glm::mat4 camera::translate(glm::mat4 transform, glm::vec3 trans_vec){

    /*pos[0]=glm::normalize(glm::cross(glm::vec3(0.f,0.f,-1.f), glm::vec3(0.f,1.f,0.f))).x * trans_vec[0];
    pos[1]=-1*trans_vec[1];
    pos[2]=-1*trans_vec[2];*/
    pos = trans_vec;
    //target = trans_vec;
    transform[3][0] = trans_vec.x;
    transform[3][1] = trans_vec.y;
    transform[3][2] = trans_vec.z;
    
    return transform;
}

glm::mat4 camera::lookat(glm::mat4 view_matrix, glm::vec3 direction){

    direction = glm::normalize(pos-target);

    //std::cout << direction.x <<  ',' << direction.y << ',' << direction.z << '\n';
    right = glm::normalize(glm::cross(direction, glm::vec3(0.f,1.f,0.f)));
    up = glm::normalize(glm::cross(right, direction));


    /*for(int i = 0; i <= 2; i++){
        view_matrix[i][0]  = right[i];
        view_matrix[i][1]  = up[i];
        view_matrix[i][2]  = direction[i];
    }*/
    


    
    view_matrix[0] = glm::vec4(right,0.f);
    view_matrix[1] = glm::vec4(up,0.f);
    view_matrix[2] = glm::vec4(direction,0.f);
    

    return view_matrix;
}

