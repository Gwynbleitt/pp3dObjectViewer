#ifndef OBJECT_H
#define OBJECT_H


class gl_object{
    public:
    
    unsigned short vertex_count;
    /* x,y,z */
    float* vertex_global_cords,
    * origin_cords;

    gl_object(unsigned short n, float arr[]);

    ~gl_object();

};

#endif