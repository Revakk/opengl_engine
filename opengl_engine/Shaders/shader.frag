#version 330
out vec4 colour;

in vec4 v_col;
in vec2 tex_coord;
in vec3 normal;

struct DirectionalLight 
{
	vec3 colour;
	float ambient_intensity;
	vec3 direction;
	float diffuse_intensity;
};

uniform sampler2D the_texture;
uniform DirectionalLight directional_light;

void main()
{
   vec4 ambient_colour = vec4(directional_light.colour,1.0f) * directional_light.ambient_intensity;

   float diffuse_factor = max(dot(normalize(normal), normalize(directional_light.direction)),0.0f);

   colour = texture(the_texture,tex_coord) * ambient_colour;
}