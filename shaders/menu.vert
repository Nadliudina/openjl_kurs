#version 330 core
layout (location = 0) in vec3 inPos;
 
uniform mat4 model;
out vec3 vertColor;
void main()
{
	gl_Position =  model * vec4(inPos, 1.0);
}