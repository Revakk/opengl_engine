#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>

class Light
{
public:
	Light();
	
	Light(float _red, float _green, float _blue, float _intensity);
	
	~Light();

	void use_light(float _ambient_intensity_location, float _ambient_colour_location);

	

private:
	glm::vec3 colour_;
	float ambient_intensity_;

};

