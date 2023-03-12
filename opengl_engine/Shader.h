#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <fstream>

#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();


	void create_from_string(std::string_view _vertex_code, std::string_view _fragment_code);
	void create_from_file(std::string_view _path,std::pair<std::string,std::string> _file_names);
	std::string read_file(std::string_view _path_to_file);

	unsigned int get_projection_location();
	unsigned int get_model_location();

	void use_shader();
	void clear_shader();

private:
	unsigned int shader_id_, uniform_projection_, uniform_model_;
	
	void compile_shader(std::string_view _vertex_code, std::string_view _fragment_code);
	void add_shader(unsigned int _the_program, std::string_view _shader_code, GLenum _shader_type);
};
