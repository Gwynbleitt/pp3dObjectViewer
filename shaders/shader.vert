#version 330 core

layout (location=0) in vec3 aPos;

out float col;

uniform mat4 view;
uniform mat4 transform;
uniform mat4 projection;

void main(){


    gl_Position =/* transform * view  * */ view * transform * vec4(aPos, 1.0) * projection;

    vec3 light = vec3(0.5,0.5,0.5);
    float dot = (aPos.x*light.x)+(aPos.y*light.y)+(aPos.z*light.z);
    dot += 5.0;
    dot *= 0.1; 

    col = dot;
}