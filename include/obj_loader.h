#include  <stdio.h>
#include  <stdlib.h>
#include  <cstring>
#include <iostream>
#include  <fstream>
#include <stdio.h>
#include <string.h>

class obj_loader{

    public:

    std::string path;

    int index_n;
    int vertex_n;
    int normal_n;

    float* vertex;
    float* normals;

    unsigned int* index;

    void load();

    float* load_vert();
    unsigned int* load_index();

};