#version 330

in vec2 fTextureUV;

uniform sampler2D textureColor;
uniform float alpha;

out vec4 FragColor;

void main()
{
	vec4 color = texture2D(textureColor, fTextureUV);
	FragColor = color;
	FragColor.a = FragColor.a * alpha;
}