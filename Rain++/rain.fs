#version 330 core
out vec4 FragColor;

in vec3 pos;
in vec3 normal;
in vec2 TexCoord;


uniform vec4 color;
uniform vec3 lightPos;

void main()
{
	vec3 lightDir = lightPos - pos;
	float lightness = dot(normalize(normal), normalize(lightDir));
	lightness = max(lightness, 0.1f);

	FragColor = lightness * color;
}