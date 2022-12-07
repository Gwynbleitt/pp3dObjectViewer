#include <iostream>
#include <string>
#include <string.h>

int main(){
    std::string line = "0//3 4/5/6";

    int tmp[6];
    int tmp_i = 0;
    int j = 0;
    std::string str;

    for(int i = 0;  i < line.length(); i++){
 

        if( line[i]<'0' || line[i]>'9'){
            str = line.substr(i-j,j);
            if(line[i])
            std::cout << std::stoi(s) << '\n';
            tmp_i++;
            j=0;
        }

        else j++;
       
    }

   // std::cout << line.substr(3,1);

    for(int i = 0; i < 6; i++){
      // std::cout << tmp[i];
    }

    std::cout << '\n';

    return 0;
}