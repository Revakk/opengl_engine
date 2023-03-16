#include "Texture.h"
#include <iostream>

Texture::Texture(const char* _file_loc): texture_id_(0),width_(0),height_(0),bit_depth_(0),file_location_(_file_loc)
{
}

Texture::Texture() : texture_id_(0), width_(0), height_(0), bit_depth_(0), file_location_("")
{
}

Texture::~Texture()
{
	
}

void Texture::load_texture()
{
	unsigned char* tex_data = stbi_load(file_location_, &width_, &height_, &bit_depth_, 0);
	if (!tex_data)
	{
		std::cout << "Failed to find: " << file_location_ << '\n';
	}

	glGenTextures(1, &texture_id_);
	glBindTexture(GL_TEXTURE_2D, texture_id_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(tex_data);
}

void Texture::use_texture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_);
}

void Texture::clear_texture()
{
	glDeleteTextures(1, &texture_id_);
	texture_id_ = 0;
	width_ = 0;
	height_ = 0;
	bit_depth_ = 0;
	file_location_ = "";
}
