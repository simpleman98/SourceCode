#version 130

in vec2 vertexPosition;

void main()
{
	gl_Position.xy = vertexPosition * 2;
	gl_Position.z = 0;
	gl_Position.w = 1;
	
}