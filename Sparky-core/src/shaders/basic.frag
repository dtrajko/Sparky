#version 330 core

layout (location = 0) out vec4 color;

in DATA
{
	vec4 position;
	vec2 uv;
	int texSlot;
	vec4 color;
} fs_in;

uniform vec4 u_color;
uniform vec2 light_pos;
uniform sampler2D textures[32];

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	vec4 texColor = fs_in.color;
	if (fs_in.texSlot > -1)
	{
		// texColor = vec4(fs_in.texSlot / 2.0, 0, 0, 1);
		texColor = texture(textures[fs_in.texSlot], fs_in.uv);
	}
	color = texColor; // * intensity;
}
