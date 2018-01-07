#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

}

in vec2 TexCoord;
in vec3 normals;
in vec3 fragPosition; 

out vec4 FragColor;

//texture samplers
uniform sampler2D texture1;
uniform vec3 viewPosition;
uniform Material material;
uniform Light light;


//uniform vec3 lightPosition;
//uniform vec3 lightColor;

void main()
{
	// ambient
	vec3 ambient = light.ambient * material.ambient;

	// diffuse
	vec3 norm = normalize(normals);
	vec3 lightDir = normalize(light.position - fragPosition); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	// specular
	vec3 viewDir = normalize(viewPosition - fragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular); 

	vec3 totalLights = ambient + diffuse + specular;

	FragColor = vec4(totalLights,1.0f) * texture(texture1, TexCoord);
}