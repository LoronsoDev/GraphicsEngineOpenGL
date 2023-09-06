#version 330

in vec4 fPos;
in vec4 fNormal;
in vec4 fColor;

out vec4 fragColor;

void main()
{
	fragColor = fColor;
}