#include "Material.h"

color Material::getAmbient(const dvec2 &  uv) const
{
	return ambientColor;
}

color Material::getDiffuse(const dvec2 & uv) const
{
	return diffuseColor;
}

color Material::getSpecular(const dvec2& uv) const
{
	return specularColor;
}



color Material::getEmisive(const dvec2& uv) const
{

	return emissiveColor * getDiffuse( uv );
}

Material operator+(Material lhs, const Material& rhs)
{
	return lhs += rhs;
}


Material operator-(Material lhs, const Material& rhs)
{
	return lhs += -1.0 * rhs;
}

Material operator*(double scalar, const Material& rhs)
{
	Material temp;

	temp.ambientColor = scalar * rhs.ambientColor;
	temp.diffuseColor = scalar * rhs.diffuseColor;
	temp.specularColor = scalar * rhs.specularColor;
	temp.emissiveColor = scalar * rhs.emissiveColor;
	temp.shininess = scalar * rhs.shininess;

	return temp;
}