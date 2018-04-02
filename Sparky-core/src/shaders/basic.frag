#version 330 core

in vec4 pos;

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;

void main()
{
	float intensity = 1.0 / length(pos.xy - light_pos);
	color = colour * intensity;
}
