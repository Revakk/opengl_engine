#pragma once
#include <GL/glew.h>

//specular lightning is a property of a material
class Material
{
public:
	Material();
	Material(float _intensity, float _shine);
	~Material();

	void use_material(unsigned int _specular_intensity_location, unsigned int _shininess_location);

private:
	float specular_intensity_;
	float shininess_;

};

