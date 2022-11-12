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

    template<typename matn>
    matn rotateX(matn matrix, int n, float angle){

        matrix[1][1] = cos(angle);
        matrix[2][1] = -sin(angle);
        matrix[1][2] = sin(angle);
        matrix[2][2] = cos(angle);
        
        return matrix;
    }
    template<typename matn>
    matn rotateY(matn matrix, int n, float angle){
        
        matrix[0][0] = cos(angle);
        matrix[2][0] = sin(angle);
        matrix[0][2] = -sin(angle);
        matrix[2][2] = cos(angle);
        
        return matrix;
    }

    template<typename matn>
    matn rotateZ(matn matrix, int n, float angle){

        matrix[0][0] = cos(angle);
        matrix[1][0] = -sin(angle);
        matrix[0][1] = sin(angle);
        matrix[1][1] = cos(angle);
        
        
        return matrix;
    }

    mat4 proj_matrix_my(mat4 matrix, float FOV, float aspect, float n, float f){

        /* 

        FRUSTUM CULLING:
        near plane -> n
        far plane  -> f

        EYE_CORDS -> CLIP_CORDS

        aspect = width/height
        

        matrix[0][0] = 2*n/(r-l); 
        matrix[0][2] = (r+l)/(r-l); 
        matrix[1][1] = 2*n/(t-b); 
        matrix[1][2] = (t+b)/(t-b); 

        */

        float t = n*tanf(FOV/2);
        float r = t * aspect;

        matrix[2][3] = -1.0f;
        matrix[0][0] = n/r; 
        matrix[1][1] = n/r; 
        matrix[2][2] = f/(n-f);
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