#version 330 core

out vec4 FragColor;

in float col;


void main(){
    FragColor = vec4(vec3(col),1.);
}