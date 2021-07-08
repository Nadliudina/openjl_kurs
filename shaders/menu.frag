#version 330 core

out vec4 outColor;
uniform vec3 butColor;
in vec2 texCoords;
uniform sampler2D ourTexture;
void main()
{
    outColor = texture(ourTexture, texCoords) ; 
	//outColor = vec4(butColor, 1.0f);
}


//#version 330 core
//
//out vec4 outColor;
//uniform vec3 butColor;
//
//void main()
//{
//	outColor = vec4(butColor, 1.0f);
//}