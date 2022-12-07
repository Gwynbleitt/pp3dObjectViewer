#include "obj_loader.h"
#include <math.h>


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
    normals = new float[vertex_n];
    index = new unsigned int[index_n];


    std::string tmp;
    std::string type;
    int tmpi;
    int arr_pos = 0;
    int arr_pos_n = 0;
    int arr_pos_f = 0;
    int j = 0;


    for(int i=0;i<=2;i++) getline(file,line);
    
    if(file.is_open()){


        //get vertex cordinates and vertex index and normal index
        
        while(getline(file,line)){

            if(line[0]='v'){

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

            else if(line[0]='f'){

                for(int i = line.length()-1; i > 0; i--){
               
                    if(line[i]!=' ' && i!=1) {
                        tmpi+=(((int)line[i]-48)*pow(10,j));
                        j++;
                    }
                    else{
                        index[ arr_pos_f - (arr_pos_f%3) + abs((arr_pos_f%3)-2)] = tmpi-1;
                        arr_pos_f++;
                        tmpi = 0;
                        j = 0;
                    }
                }
            
            }
        }

        file.close();
        file.open( path );

        while(getline(file,line)){
            type = line.substr(0,2);
            if(type == "vn"){

            }
        }
        

        //reset
        //get normals based on indieces

        /* 

        for every line ->

        look up position of i in normal index array

        find value on same position but in vertex index array

        insert the value into returned index

        */

        //e.g normal 1 -> vertex 47
        //this way referencing vertex index will have also correct normal
        //vertex attribute array should look like this:
        /*

        vx1, vy1, vz1, nx23, ny23, nz23,
        ...

        */
    }

    file.close();
    //file.open( path );




    //indicies


}