#version 330 core

layout (location=0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 col;

uniform mat4 view;
uniform vec3 camera_pos;
uniform mat4 projection;

uniform vec3 light_src;

void main(){


    gl_Position = view * vec4(aPos+camera_pos, 1.0)  * projection;


    col = vec3
    (
        aColor.x*light_src.x + 
        aColor.y*light_src.y + 
        aColor.z*light_src.z
    );
}