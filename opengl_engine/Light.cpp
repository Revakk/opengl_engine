#include "Light.h"

Light::Light()
{
	colour_ = glm::vec3(1.0f, 1.0f, 1.0f);
	ambient_intensity_ = 1.0f;
	diffuse_intensity_ = 0.0f;
}

Light::Light(float _red, float _green, float _blue, float _intensity, float _diffuse_intensity)
{
	colour_ = glm::vec3(_red, _green, _blue);
	ambient_intensity_ = _intensity;

	diffuse_intensity_ = _diffuse_intensity;
}

Light::~Light()
{
}

