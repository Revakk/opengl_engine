#pragma once

#include <GL/glew.h>
#include <stb_image.h>

class Texture
{
public:
	Texture();
	Texture(const char* file_loc);
	~Texture();

	void load_texture();
	void use_texture();
	void clear_texture();



private:
	unsigned int texture_id_;
	int width_, height_, bit_depth_;

	const char* file_location_;
};

