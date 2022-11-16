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

    float* load_vert();
    unsigned int* load_index();

};