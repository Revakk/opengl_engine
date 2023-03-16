#version 330
out vec4 colour;

in vec4 v_col;
in vec2 tex_coord;

uniform sampler2D the_texture;

void main()
{ 
   colour = texture(the_texture,tex_coord);
}