#include "Material.h"

Material::Material()
{
	specular_intensity_ = 0;
	shininess_ = 0;
}

Material::Material(float _intensity, float _shine): specular_intensity_(_intensity), shininess_(_shine)
{
}

Material::~Material()
{
}

void Material::use_material(unsigned int _specular_intensity_location, unsigned int _shininess_location)
{
	glUniform1f(_specular_intensity_location, specular_intensity_);
	glUniform1f(_shininess_location, shininess_);
}
