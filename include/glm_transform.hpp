#ifndef GLM_TRANSFORM_H
#define GLM_TRANSFORM_H

#include <glm/glm.hpp>
#include <math.h>
#include <iostream>

namespace glm{

    /*
    struct vec4{
        float x,y,z,w;
    };
#include "glm_transform.hpp"
    struct mat4{
        vec4 x,y,z,w;
    }*/
    
    

    template<typename matn>
    matn translate(matn matrix, int n, vec3 vec){
        matrix[n-1][0] = vec[0];
        matrix[n-1][1] = vec[1];
        matrix[n-1][2] = vec[2];
        return matrix;
    }


    mat4 proj_matrix_my(mat4 matrix, float FOV, float aspect, float n, float f){

        /* 

        FRUSTUM CULLING:
        near plane -> n
        far plane  -> f

        */

        float t = n*tanf(FOV/2);
        float r = t * aspect;

        matrix[2][3] = -1.0f;
        matrix[0][0] = n/r; 
        matrix[1][1] = n/t; 
        matrix[2][2] = (f+n)/(n-f);
        matrix[3][2] = 2*f*n/(n-f);

        return matrix;
    }



    template<typename matn>
    void print_matrix(matn matrix, int n){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                std::cout << matrix[j][i] << ',';
            }
            std::cout << '\n';
        }
    }




};

#endif