#version 330

in vec2 fTextureUV;

uniform sampler2D textureColor;

out vec4 FragColor;

void main()
{
	FragColor = texture2D(textureColor, fTextureUV);
}