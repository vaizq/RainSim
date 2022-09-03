#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;


out vec3 pos;
out vec3 normal;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	pos = (model * vec4(aPos, 1.0f)).xyz;
	normal = aNormal;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}