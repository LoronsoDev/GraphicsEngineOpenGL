#version 330

out vec4 fragColor;

in vec4 position;

void main()
{
	fragColor=vec4(1.0f,1.0f,1.0f,0.0f) + position;
}