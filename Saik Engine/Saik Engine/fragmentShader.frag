#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	//FragColor = texture(texture1, TexCoord);
	FragColor = vec4(lightColor * objectColor, 1.0);
}