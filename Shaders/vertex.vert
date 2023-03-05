#version 330


layout (location = 0) in vec3 vPos;
//layout (location = 1) in vec2 aTexCoords;
uniform mat4 mMat;

out vec4 position;

void main()
{
//	TexCoords = aTexCoords;
	gl_Position=mMat*vec4(vPos,1.0);
	position = gl_Position;
}