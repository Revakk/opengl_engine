#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	direction_ = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(float _red, float _green, float _blue,
								   float _intensity, float _diffuse_intensity,
								   float _x_direction, float _y_direction, float _z_direction) : Light(_red,_green,_blue,_intensity,_diffuse_intensity)
{
	
	direction_ = glm::vec3(_x_direction, _y_direction, _z_direction);
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::use_light(float _ambient_intensity_location,float _ambient_colour_location, float _diffuse_intensity_location, float _direction_location)
{
	glUniform3f(_ambient_colour_location, colour_.x, colour_.y, colour_.z);
	glUniform1f(_ambient_intensity_location, ambient_intensity_);
	glUniform3f(_direction_location, direction_.x, direction_.y, direction_.z);
	glUniform1f(_diffuse_intensity_location, diffuse_intensity_);
}

void DirectionalLight::rotate_light(float _time)
{
	direction_.y = std::sin(_time / 2.0f);
}

