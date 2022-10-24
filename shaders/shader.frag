#version 330 core

out vec4 FragColor;

in vec3 position;
in vec3 ourcolor;


void main(){
    FragColor = vec4(position,1.0);
}