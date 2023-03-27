#include "Shader.h"
#include <filesystem>

Shader::Shader()
{
	shader_id_ = 0;
	uniform_model_ = 0;
	uniform_projection_ = 0;
}


Shader::~Shader()
{
    clear_shader();
}


void Shader::create_from_string(std::string_view _vertex_code, std::string_view _fragment_code)
{
	compile_shader(_vertex_code,_fragment_code);
}

void Shader::create_from_file(std::string_view _path, std::pair<std::string, std::string> _file_names)
{
    std::cout << "creating shaders from files: " << _path.data() + _file_names.first << ", " << _path.data() + _file_names.first << '\n';

    std::string vert_shader = read_file(_path.data() + _file_names.first);
    std::string frag_shader = read_file(_path.data() + _file_names.second);

    compile_shader(vert_shader, frag_shader);
}

std::string Shader::read_file(std::string_view _path_to_file)
{
    std::string file_content;
    std::ifstream file_stream(_path_to_file.data(), std::ios::in);

    if (!file_stream.is_open())
    {
        std::runtime_error("cannot read shader file");
    }

    std::string line = "";
    while (!file_stream.eof())
    {
        std::getline(file_stream, line);
        file_content.append(line + "\n");
    }

    file_stream.close();

    return file_content;
}

unsigned int Shader::get_projection_location()
{
	return uniform_projection_;
}

unsigned int Shader::get_model_location()
{
	return uniform_model_;
}

unsigned int Shader::get_view_location()
{
    return uniform_view_;
}

unsigned int Shader::get_ambient_intensity_location()
{
    return uniform_ambient_intensity_;
}

unsigned int Shader::get_ambient_colour_location()
{
    return uniform_ambient_colour_;
}

unsigned int Shader::get_diffuse_intensity_location()
{
    return uniform_diffuse_intensity_;
}

unsigned int Shader::get_direction_location()
{
    return uniform_direction_;
}

unsigned int Shader::get_eye_position_location()
{
    return uniform_eye_position;
}

unsigned int Shader::get_specular_intensity_location()
{
    return uniform_specular_intensity_;
}

unsigned int Shader::get_shininess_location()
{
    return uniform_shininess_;
}

void Shader::use_shader()
{
    if (shader_id_)
    {
        glUseProgram(shader_id_);
    }
    else 
    {
        std::runtime_error("shader must be ready");
    }
    
}

void Shader::clear_shader()
{
    if (shader_id_)
    {
        glDeleteProgram(shader_id_);
        shader_id_ = 0;
    }
    uniform_model_ = 0;
    uniform_projection_ = 0;
}

void Shader::compile_shader(std::string_view _vertex_code, std::string_view _fragment_code)
{
    // create shader program

    shader_id_ = glCreateProgram();

    // validate if there are no errors
    if (!shader_id_) {
        std::cout << "Error creating shader program" << '\n';
        return;
    }

    //add shader code to the program
    add_shader(shader_id_, _vertex_code, GL_VERTEX_SHADER);
    add_shader(shader_id_, _fragment_code, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar e_log[1024] = { 0 };

    // link the program and create "executable" on GPU
    glLinkProgram(shader_id_);

    // validate the program
    glValidateProgram(shader_id_);

    // get the validation status
    glGetProgramiv(shader_id_, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader_id_, sizeof(e_log), NULL, e_log);
        std::cout << "Error validating program " << e_log << '\n';
        return;
    }

    uniform_model_ = glGetUniformLocation(shader_id_, "model");
    uniform_projection_ = glGetUniformLocation(shader_id_, "projection");
    uniform_view_ = glGetUniformLocation(shader_id_, "view");
    uniform_ambient_colour_ = glGetUniformLocation(shader_id_, "directional_light.colour");
    uniform_ambient_intensity_ = glGetUniformLocation(shader_id_, "directional_light.ambient_intensity");
    uniform_direction_ = glGetUniformLocation(shader_id_, "directional_light.direction");
    uniform_diffuse_intensity_ = glGetUniformLocation(shader_id_, "directional_light.diffuse_intensity");
    uniform_eye_position = glGetUniformLocation(shader_id_, "eye_position");
    uniform_specular_intensity_ = glGetUniformLocation(shader_id_, "material.specular_intensity");
    uniform_shininess_ = glGetUniformLocation(shader_id_, "material.shininess");
}

void Shader::add_shader(unsigned int _the_program, std::string_view _shader_code, GLenum _shader_type)
{
    // create global shader
    GLuint shader = glCreateShader(_shader_type);
    const GLchar* the_code[1];
    the_code[0] = _shader_code.data();

    GLint code_length[1];
    code_length[0] = strlen(_shader_code.data());

    //add code to the shader and compile the shader
    glShaderSource(shader, 1, the_code, code_length);
    glCompileShader(shader);

    GLint result = 0;
    GLchar e_log[1024] = { 0 };

    // check the compile result
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(shader, sizeof(e_log), NULL, e_log);
        std::cout << "Error compiling shader " << e_log << " of type: " << _shader_type << '\n';
        return;
    }

    //atach compiled shader to shader program
    glAttachShader(_the_program, shader);
}
