#version 330 core

layout (location=0) in vec3 aPos;

out vec3 col;

uniform mat4 view;
uniform vec3 camera_pos;
uniform mat4 projection;

void main(){


    gl_Position = view * vec4(aPos+camera_pos, 1.0)  * projection;


    col = aPos;
}