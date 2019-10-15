#pragma once

#include "Defines.h"

/**
* Simple struct that represents the materials properties of a surface. Material properties
* deterine the color of and object and how it interacts with light sources in a scene.
*/
struct Material
{
protected:

	/** @brief	Emissive color of the surface */
	color emissiveColor = BLACK;	
	
	/** @brief	Ambient color of the surface (usually the same as the diffuseColor). */
	color ambientColor = GRAY;

	/** @brief	Diffuse color of the surface. */
	color diffuseColor = GRAY;

	/** @brief	Specular color of the surface (white for a shiny surface). */
	color specularColor = WHITE;

public:

	/** @brief	Shininess exponent for specular lighting calculations. */
	double shininess = 128.0;

	/**
	 * @fn	Material( const color & diffuseColor = WHITE )
	 *
	 * @brief	Constructor
	 *
	 * @param	diffuseColor	(Optional) The diffuse color of the surface.
	 */
	Material( const color & diffuseColor = WHITE )
		: diffuseColor( diffuseColor ), ambientColor( diffuseColor )
	{

	}

	virtual color getAmbient(const dvec2 & uv = dvec2(0.5, 0.5)) const;

	virtual color getDiffuse(const dvec2& uv = dvec2(0.5, 0.5)) const;

	virtual color getSpecular(const dvec2& uv = dvec2(0.5, 0.5)) const;

	virtual color getEmisive(const dvec2& uv = dvec2(0.5, 0.5)) const;

	Material& operator+=(const Material& rhs)
	{
		this->ambientColor += rhs.ambientColor;
		this->diffuseColor += rhs.diffuseColor;
		this->specularColor += rhs.specularColor;
		this->emissiveColor += rhs.emissiveColor;
		this->shininess += rhs.shininess;

		return *this;
	}

	friend Material operator+(Material lhs, const Material& rhs);
	friend Material operator-(Material lhs, const Material& rhs);
	friend Material operator*(double scalar, const Material& rhs);

};