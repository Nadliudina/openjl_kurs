#version 330 core

out vec4 outColor;

uniform vec3 PointsColor;

void main()
{
	outColor = vec4(PointsColor, 1.0f);
}