#include "obj_loader.h"
#include <math.h>

/*float* obj_loader::load_vert(){

    std::string line, tmp;
    std::ifstream file;
    vertex_n = 0;
    int arr_pos = 0;

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
    index_n = 0;
    int arr_pos = 0;
    int j = 0;
    unsigned int tmp = 0;

    file.open( path );

    for(int i=0;i<=2016;i++) getline(file,line);
    
    if(file.is_open()){
        while(getline(file,line)&&line[0]=='f'){
            index_n++;
        }
    }

    file.close(); 

    std::cout << index_n << '\n';

    unsigned int* readi = new unsigned int[3*index_n];

    file.open( path );

    for(int i=0;i<=2016;i++) getline(file,line);

    
    
    if(file.is_open()){

        //arr_pos = 0;
        while(getline(file,line)&&line[0]=='f'){
            
            //std::cout << line;
            for(int i = line.length()-1; i > 0; i--){
               
                
                if(line[i]!=' ' && i!=1) {
                    tmp+=(((int)line[i]-48)*pow(10,j));
                    j++;
                }
                else{
                    readi[ arr_pos - (arr_pos%3) + abs((arr_pos%3)-2)] = tmp-1;
                    //std::cout << "ap" << arr_pos << ',';
                    arr_pos++;
                    tmp = 0;
                    j = 0;
                }
                
            }
            
          
        }
    }
    
    

    file.close(); 
    return readi;
}
*/

void obj_loader::load(){

    std::string line;
    std::ifstream file;

    index_n = 0;
    vertex_n = 0;

    file.open( path );

    for(int i=0;i<=2;i++) getline(file,line);

    if(file.is_open()){
        while(getline(file,line)&&line[0]=='v'){
            vertex_n++;
        }

        //getline(file,line);

        while(getline(file,line)&&line[0]=='f'){
            index_n++;
        }
    }

    index_n *= 3;
    vertex_n *= 3;

    file.close();
    file.open( path );

    vertex = new float[vertex_n];
    index = new unsigned int[index_n];


    std::string tmp;
    int tmpi;
    int arr_pos = 0;
    int j = 0;

    for(int i=0;i<=2;i++) getline(file,line);
    
    if(file.is_open()){
        while(getline(file,line)&&line[0]=='v'){
            
            for(int i = 2; i < line.length()+1; i++){
                if(line[i]!=' ' && i!=line.length()) {
                    tmp.push_back(line[i]);
        
                }
                else{
                    vertex[arr_pos] = std::stof(tmp,NULL)/2;
                    arr_pos++;
                    tmp.clear();
                }
            }
        }

        //getline(file,line);
        arr_pos = 0;

        while(getline(file,line)&&line[0]=='f'){
            
            //std::cout << line;
            for(int i = line.length()-1; i > 0; i--){
               
                
                if(line[i]!=' ' && i!=1) {
                    tmpi+=(((int)line[i]-48)*pow(10,j));
                    j++;
                }
                else{
                    index[ arr_pos - (arr_pos%3) + abs((arr_pos%3)-2)] = tmpi-1;
                   // std::cout << index[arr_pos] << ',';
                    arr_pos++;
                    tmpi = 0;
                    j = 0;
                }
                
            }

           // std::cout << '\n';
            
          
        }
    }

    file.close();
    //file.open( path );




    //indicies


}