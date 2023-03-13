#version 330


in vec4 vPos;

uniform mat4 mMat;

out vec4 position;

void main()
{
	gl_Position= mMat * vPos;
	position = gl_Position;
}