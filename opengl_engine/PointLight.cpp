#include "PointLight.h"

PointLight::PointLight()
{
	position_ = glm::vec3(0.0f, 0.0f, 0.0f);
	constant_ = 1.0f; //cannot divide by 0 L/ax^2+bx+c
	linear_ = 0.0f;
	exponent_ = 0.0f;
}

PointLight::PointLight(float _red, float _green, float _blue,
					   float _intensity, float _diffuse_intensity,
					   float _x_pos, float _y_pos, float _z_pos,
					   float _con, float _lin, float _exp):Light(_red,_green,_blue,_intensity,_diffuse_intensity)
{
	position_ = glm::vec3(_x_pos, _y_pos, _z_pos);
	constant_ = _con;
	linear_ = _lin;
	exponent_ = _exp;
}

void PointLight::use_light(float _ambient_intensity_location, float _ambient_colour_location,
	float _diffuse_intensity_location, float _position_location,float _constant_location , float _linear_location, float _exponent_location)
{
	glUniform3f(_ambient_colour_location, colour_.x, colour_.y, colour_.z);
	glUniform1f(_ambient_intensity_location, ambient_intensity_);
	glUniform1f(_diffuse_intensity_location, diffuse_intensity_);

	glUniform3f(_position_location, position_.x, position_.y, position_.z);
	glUniform1f(_constant_location, constant_);
	glUniform1f(_linear_location, linear_);
	glUniform1f(_exponent_location, exponent_);

}

PointLight::~PointLight()
{
}
