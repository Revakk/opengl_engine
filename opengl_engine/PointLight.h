#pragma once
#include "Light.h"

class PointLight: public Light
{
public:
	PointLight();

	PointLight(float _red, float _green, float _blue,
		float _intensity, float _diffuse_intensity,
		float _x_pos, float _y_pos,float _z_pos,
		float _con, float _lin, float _exp);

	void use_light(float _ambient_intensity_location, float _ambient_colour_location,
		float _diffuse_intensity_location, float _position_location,float _constant_location, float _linear_location, float _exponent_location);

	~PointLight();

private:
	glm::vec3 position_;

	float constant_, linear_, exponent_;
};

