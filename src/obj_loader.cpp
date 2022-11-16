#include "obj_loader.h"
#include <math.h>

float* obj_loader::load_vert(){

    std::string line, tmp;
    std::ifstream file;
    int vertex_n,arr_pos = 0;

    file.open( path );

    for(int i=0;i<=3;i++) getline(file,line);

    if(file.is_open()){
        while(getline(file,line)&&line[0]=='v'){
            vertex_n++;
        }
    }
    file.close(); 

    float* read = new float[vertex_n*3];

    file.open( path );

    for(int i=0;i<=3;i++) getline(file,line);
    
    if(file.is_open()){

        
        while(getline(file,line)&&line[0]=='v'){
            for(int i = 2; i < line.length()+1; i++){
                if(line[i]!=' ' && i!=line.length()) {
                    tmp.push_back(line[i]);
        
                }
                else{
                    read[arr_pos] = std::stof(tmp,NULL);
                    arr_pos++;
                    tmp.clear();
                }
            }
        }
    }

    file.close(); 

    return read;
}

unsigned int* obj_loader::load_index(){

    std::string line;
    std::ifstream file;
    int index_n,arr_pos,j = 0;
    unsigned int tmp = 0;

    file.open( path );

    for(int i=0;i<=2016;i++) getline(file,line);
    
    if(file.is_open()){
        while(getline(file,line)&&line[0]=='f'){
            index_n++;
        }
    }

    file.close(); 

    unsigned int* read = new unsigned int[index_n*3];

    file.open( path );

    for(int i=0;i<=2016;i++) getline(file,line);

    
    
    if(file.is_open()){

        

        std::cout << line << '\n';
        
        while(getline(file,line)&&line[0]=='f'){
            
            
            for(int i = line.length()-1; i >= 1; i--){
               //std::cout << line[i];
                
                if(line[i]!=' ' && i!=1) {
                    tmp+=(((int)line[i]-48)*pow(10,j));
                    j++;
                }
                else{
                    read[abs(arr_pos-2)] = tmp;
                    std::cout << tmp << ',';
                    arr_pos++;
                    tmp = 0;
                    j = 0;
                }
                
            }
            
            std::cout << '\n';
        }
    }
    
    

    file.close(); 
    return NULL;
}