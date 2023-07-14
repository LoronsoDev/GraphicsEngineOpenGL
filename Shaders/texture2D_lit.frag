#version 330

struct Light
{
	//LIGHT SETTINGS
	int type;
	vec4 color;
	vec3 specularColor;
	float intensity;
	float linearAttenuation;
	float quadraticAttenuation;
	vec3 position;
	vec3 direction;
};

uniform Light lights[8];
uniform int numLights;
uniform sampler2D textureColor;

out vec4 fragColor;

in vec4 fPos;
in vec4 fNormal;
in vec4 fColor;
in vec2 fTextureUV;

uniform vec3 ambient;
uniform float shininess;

uniform vec4 viewPos;

void main()
{
	//Contributions...
	vec3 cc_diff = vec3(0.);
	vec3 cc_spec = vec3(0.);		

	vec4 norm = normalize(fNormal);

	vec4 lightPos;
	vec4 lightDir;
	float diff;
	vec3 diffuse;

	vec3 viewDir;
	vec3 reflectDir;
	float spec;
	vec3 specular;

	for(int i = 0; i < numLights; ++i)
	{
		switch(lights[i].type)
		{
			case 0:     //DIRECTIONAL

				// lightPos = vec4(lights[i].position.xyz, 0.);
				lightDir = vec4(normalize(lights[i].direction.xyz), 0.);
				diff = max(dot(norm, lightDir), 0.0);
				diffuse = diff * lights[i].color.xyz;

				viewDir = vec3(normalize(viewPos - fPos));
				reflectDir = vec3(reflect(-lightDir, norm));  
				spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
				specular = spec * lights[i].specularColor.xyz;

				cc_diff += diffuse * lights[i].intensity;
				cc_spec += specular * lights[i].intensity;

				break;
			case 1:		//POINT

				float distance    = length(lights[i].position.xyz - fPos.xyz);
				float attenuation = 1.0 / (1.0 + lights[i].linearAttenuation * distance + 
    		    lights[i].quadraticAttenuation * (distance * distance)); 

				lightPos = vec4(lights[i].position.xyz, 0.);
				lightDir = normalize(lightPos - fPos);
				diff = max(dot(norm, lightDir), 0.0);
				diffuse = diff * lights[i].color.xyz;

				viewDir = vec3(normalize(viewPos - fPos));
				reflectDir = vec3(reflect(-lightDir, norm));  
				spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
				specular = spec * lights[i].specularColor.xyz;

				diffuse *= attenuation;
				specular *= attenuation;

				cc_diff += diffuse * lights[i].intensity;
				cc_spec += specular * lights[i].intensity;

				break;
			case 2:		//SPOT

				break;
			case 3:		//AREA

				break;
		}
	}

	vec3 result = (ambient + cc_diff + cc_spec) * fColor.xyz;
	fragColor = vec4(result, 1.0) * texture2D(textureColor, fTextureUV);
}