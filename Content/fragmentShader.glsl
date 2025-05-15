#version 330 core

in vec4 pos;

out vec4 FragColor;

uniform sampler2D texture;

void main()
{
   FragColor = pos;
}