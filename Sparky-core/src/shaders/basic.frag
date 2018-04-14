#version 330 core

layout (location = 0) out vec4 color;

in DATA
{
	vec4 position;
	vec2 uv;
	vec4 color;
} fs_in;

uniform vec4 u_color;
uniform vec2 light_pos;
uniform sampler2D tex;

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	// color = fs_in.color * intensity;
	color = texture(tex, fs_in.uv) * intensity;
}
