#include "Plane.h"


Plane::Plane(const dvec3 & point, const dvec3 & normal, const color & material)
	: ImplicitSurface(material), a(point), n(normalize(normal))
{
}


Plane::Plane(std::vector<dvec3> vertices, const color & material)
	: ImplicitSurface(material)
{
	a = vertices[0];

	n = glm::normalize(glm::cross(vertices[2] - vertices[1], vertices[0] - vertices[1]));
}


HitRecord Plane::findIntersect( const Ray & ray )
{
	HitRecord hitRecord;

	double denominator = glm::dot(ray.direct, n);
	if (denominator < 0) {
		double t = glm::dot(a - ray.origin, n) / denominator;
		hitRecord.surfaceNormal = n;
		hitRecord.interceptPoint = ray.origin + t * ray.direct;
		hitRecord.t = t;
		hitRecord.material = material;
	}
	else
	{
		hitRecord.t = INFINITY;
	}
	return hitRecord;

} // end findClosestIntersection

