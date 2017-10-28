#version 130

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;


out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

void main()
{
	gl_Position.xy = vertexPosition * 1;
	gl_Position.z = 0;
	gl_Position.w = 1;
	
	fragmentColor = vertexColor;
	fragmentPosition = vertexPosition;
	fragmentUV = vec2(vertexUV.x,1.0 - vertexUV.y);
}