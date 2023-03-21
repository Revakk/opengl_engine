#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>

class Light
{
public:
	Light();
	
	Light(float _red, float _green, float _blue, float _intensity,
		float _x_direction, float _y_direction, float _z_direction, float _diffuse_intensity);
	
	~Light();

	void use_light(float _ambient_intensity_location, float _ambient_colour_location,
		float _diffuse_intensity_location, float _direction_location);

	

private:
	glm::vec3 colour_;
	float ambient_intensity_;

	// diffuse light
	glm::vec3 direction_;
	float diffuse_intensity_;

};

