#pragma once
#include "Light.h"

class DirectionalLight :
	public Light
{
public:
	DirectionalLight();

	DirectionalLight(float _red, float _green, float _blue, 
					 float _intensity, float _diffuse_intensity,
					 float _x_direction, float _y_direction, float _z_direction);

	void rotate_light(float _time);
	~DirectionalLight();

	void use_light(float _ambient_intensity_location, float _ambient_colour_location,
		float _diffuse_intensity_location, float _direction_location);

private:
	// diffuse light
	glm::vec3 direction_;
};

