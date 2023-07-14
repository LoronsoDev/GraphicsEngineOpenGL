#version 330

in vec4 vPos;
in vec4 vNormal;
in vec4 vColor;
in vec2 vTextureUV;

uniform mat4 MVP;
uniform mat4 M;

out vec4 fNormal;
out vec4 fColor;
out vec4 fPos;
out vec2 fTextureUV;

void main()
{
	gl_Position = MVP * vPos;
	fPos = gl_Position;
	fNormal = normalize(vec4(mat3(inverse(transpose(M))) * vNormal.xyz, 0.0f));
	fColor = vColor;
	fTextureUV = vTextureUV;
}