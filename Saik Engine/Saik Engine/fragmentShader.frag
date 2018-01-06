#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 normals;

// texture samplers
uniform sampler2D texture1;
uniform vec3 ambientLight;

void main()
{
	FragColor = texture(texture1, TexCoord) * vec4(ambientLight, 1.0f);
}