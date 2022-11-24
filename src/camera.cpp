#include "camera.h"
#include <iostream>

camera::camera(glm::vec3 cords, unsigned int shader_program, const char* var_name){
    glUniform3f(glGetUniformLocation(shader_program, var_name), cords.x,cords.y,cords.z);
}

glm::mat4 camera::lookat(glm::mat4 view_matrix, glm::vec3 d, glm::vec3 t){

    r = glm::normalize(glm::cross(d, glm::vec3(0.f,1.f,0.f)));
    u = glm::normalize(glm::cross(r, d));


    for(int i = 0; i <= 2; i++){
        view_matrix[i][0]  = r[i];
        view_matrix[i][1]  = u[i];
        view_matrix[i][2]  = d[i];
    }

    view_matrix[3][0] = (r.x*t.x)+(r.y*t.y)+(r.z*t.z);
    view_matrix[3][1] = (u.x*t.x)+(u.y*t.y)+(u.z*t.z);
    view_matrix[3][2] = (d.x*t.x)+(d.y*t.y)+(d.z*t.z);

    return view_matrix;
}

