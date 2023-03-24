#include "Light.h"

Light::Light()
{
	colour_ = glm::vec3(1.0f, 1.0f, 1.0f);
	ambient_intensity_ = 1.0f;
	direction_ = glm::vec3(0.0f, -1.0f, 0.0f);
	diffuse_intensity_ = 0.0f;
}

Light::Light(float _red, float _green, float _blue, float _intensity,float _x_direction, float _y_direction, float _z_direction, float _diffuse_intensity)
{
	colour_ = glm::vec3(_red, _green, _blue);
	ambient_intensity_ = _intensity;

	direction_ = glm::vec3(_x_direction, _y_direction, _z_direction);
	diffuse_intensity_ = _diffuse_intensity;
}

Light::~Light()
{
}

void Light::use_light(float _ambient_intensity_location, float _ambient_colour_location, float _diffuse_intensity_location, float _direction_location)
{
	glUniform3f(_ambient_colour_location, colour_.x, colour_.y, colour_.z);
	glUniform1f(_ambient_intensity_location, ambient_intensity_);
	glUniform3f(_direction_location, direction_.x, direction_.y, direction_.z);
	glUniform1f(_diffuse_intensity_location, diffuse_intensity_);
}
