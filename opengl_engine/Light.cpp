#include "Light.h"

Light::Light()
{
	colour_ = glm::vec3(1.0f, 1.0f, 1.0f);
	ambient_intensity_ = 1.0f;
}

Light::Light(float _red, float _green, float _blue, float _intensity)
{
	colour_ = glm::vec3(_red, _green, _blue);
	ambient_intensity_ = _intensity;
}

Light::~Light()
{
}

void Light::use_light(float _ambient_intensity_location, float _ambient_colour_location)
{
	glUniform3f(_ambient_colour_location, colour_.x, colour_.y, colour_.z);
	glUniform1f(_ambient_intensity_location, ambient_intensity_);
}
