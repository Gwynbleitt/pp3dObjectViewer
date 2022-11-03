#include <glm/glm.hpp>

namespace glm{

    template<typename matn>
    matn translate(matn matrix, int n, float x, float y, float z){
        matrix[n-1][0] = x;
        matrix[n-1][1] = y;
        matrix[n-1][2] = z;
        return matrix;
    }

    template<typename matn>
    matn rotate(matn matrix, int n, vec3 axis_vec, int angle/* degrees */){
        return matrix;
    }

    template<typename matn>
    void print_matrix(matn matrix, int n){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                std::cout << matrix[i][j];
            }
            std::cout << '\n';
        }
    }

};