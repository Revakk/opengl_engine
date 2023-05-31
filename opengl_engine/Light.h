#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>

class Light
{
public:
	Light();
	
	Light(float _red, float _green, float _blue, float _intensity, float _diffuse_intensity);
	
	~Light();	

protected:
	glm::vec3 colour_;
	float ambient_intensity_;
	float diffuse_intensity_;

};

