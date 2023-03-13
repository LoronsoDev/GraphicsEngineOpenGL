#version 330


in vec4 vPos;
in vec2 vTextureUV;

uniform mat4 MVP;

out vec2 fTextureUV;

void main()
{
	gl_Position = MVP * vPos;

	fTextureUV = vTextureUV;
}