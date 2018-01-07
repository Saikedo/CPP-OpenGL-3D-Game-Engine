#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 normals;
in vec3 fragPosition;


struct Material {
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  

//texture samplers
uniform sampler2D texture1;
uniform vec3 ambientLight;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 viewPosition;
uniform float specularStrength;

void main()
{
	vec3 norm = normalize(normals);
	vec3 lightDir = normalize(lightPosition - fragPosition); 

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPosition - fragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;  

	FragColor = vec4((ambientLight + diffuse + specular), 1.0f) * texture(texture1, TexCoord);
}