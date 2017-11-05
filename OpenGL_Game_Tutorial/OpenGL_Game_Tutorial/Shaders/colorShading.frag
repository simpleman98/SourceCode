#version 130
in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;
 
out vec4 color;

uniform float time;
uniform sampler2D mySampler;
void main()
{

	 vec4 textureColor = texture(mySampler,fragmentUV);
	
	
	color = fragmentColor;
	
	//color = vec4(fragmentColor.r * (cos(fragmentPosition.x * 4+time)+1.0) * 0.5,
	//			 fragmentColor.g * (cos(fragmentPosition.y * 8+time)+1.0) * 0.5,
	// 			 fragmentColor.b * (cos(fragmentPosition.x * 2+time)+1.0) * 0.5,
	//			 fragmentColor.a);
					
}