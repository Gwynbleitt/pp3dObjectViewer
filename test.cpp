#include <iostream>
#include <string>
#include <string.h>

int main(){
    std::string line = "f 1526//78 16//55 541//68";

    int arr[3][3];
    int tmp_x, tmp_y, j = 0;

    for(int i = 2;  i < line.length()+1; i++){

        if(line[i]<'0' || line[i]>'9'){

            arr[tmp_x][tmp_y] = j ? std::stoi(line.substr(i-j,j)) : -1;
            
            if(!tmp_x%3){
                tmp_x = 0;
                tmp_y++;
            }else tmp_x++;
            
            j=0;
        } else j++;       
    }

    for(int q = 0; q < 3; q++){
        for(int p = 0; p < 3; p++){
             std::cout << arr[p][q] << ' ';
        }
        std::cout << '\n';
    }        

    
    return 0;
}