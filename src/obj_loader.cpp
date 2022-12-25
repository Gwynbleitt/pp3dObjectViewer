#include "obj_loader.h"
#include <math.h>
#include <algorithm> 
#include <string>


int obj_loader::find(unsigned int* arr, int a, int size)
{

    // NOT FOUND -> -1

    int i = 0;
    bool out = 0;

    while(i < size)
    {
        if(arr[i] == a)
        {
            out = 1;
            break;
        }

        i++;
    }

    return out == 1 ? i : -1;

}


void obj_loader::load()
{

    std::string line;
    std::ifstream file;
    std::string type;

    index_n = 0;
    vertex_n = 0;
    normal_n = 0;

    file.open( path );

    for(int i=0;i<=2;i++) getline(file,line);

    if(file.is_open()){

        while(getline(file,line)){
            type = line.substr(0,2);
            if(type=="v ") vertex_n++;
            if(type=="f ") index_n++;
            if(type=="vn") normal_n++;
        }
    }

    index_n *= 3;
    vertex_n *= 3;
    normal_n *= 3;

    file.close();
    file.open( path );

    vertex = new float[vertex_n];
    normals = new float[vertex_n];
    index = new unsigned int[index_n];
    normal_index = new unsigned int[index_n];


    std::string tmp;
    int tmpi;
    int arr_pos = 0;
    int arr_pos_n = 0;
    int arr_pos_f = 0;
    int j = 0;

    int arr[3][3];
    int tmp_x = 0;
    int tmp_y = 0;
    
    if(file.is_open()){

        
        while(getline(file,line))
        {

            type = line.substr(0,2);

            if(type=="v "){
                //std::cout << line << '\n';
                for(int i = 2; i < line.length()+1; i++)
                {
                    if(line[i]!=' ' && i!=line.length())
                    {
                        tmp.push_back(line[i]);
                    }
                    else
                    {
                        vertex[arr_pos] = std::stof(tmp,NULL);
                        arr_pos++;
                        tmp.clear();
                    }
                }
                
            }
            
            
            else if(type=="f "){

                for(int i = 2;  i < line.length()+1; i++)
                {

                    if(line[i]<'0' || line[i]>'9')
                    {

                        arr[tmp_x][tmp_y] = j ? std::stoi(line.substr(i-j,j)) : -1;
                        
                        if(!(tmp_x%3))
                        {
                            tmp_x = 0;
                            tmp_y++;
                        }
                        else tmp_x++;
                        
                        j = 0;
                    } else j++;       
                }

                for(int q = 0; q < 3; q++){
                        index[arr_pos_f] = arr[q][0]-1;
                        normal_index[arr_pos_f] = arr[q][2]-1;
                        arr_pos_f++;
                }   
                
                tmp_x, tmp_y = 0; 
            
            }
            
        }

        file.close();
        file.open( path );

        j = 0;
        arr_pos = 0;
        tmp.clear();

        int vnb[3];

        if(file.is_open()){           

            while(getline(file, line))
            {

                type=line.substr(0,2);
                
                if(type=="vn")
                {

                    for(int i = 3; i < line.length()+1; i++){
                        if(line[i]!=' ' && i!=line.length()) {
                            tmp.push_back(line[i]);
                        }
                        else{
                            normals[3*index[find(normal_index, j, normal_n)]+arr_pos] = std::stof(tmp, NULL);
                            arr_pos++;

                            tmp.clear();
                        }
                    }
                    arr_pos = 0;
                    j++;
                }
                
            }
        }
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