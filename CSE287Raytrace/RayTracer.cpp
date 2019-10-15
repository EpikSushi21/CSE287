#include "RayTracer.h"


RayTracer::RayTracer(FrameBuffer& cBuffer, color defaultColor)
	:colorBuffer(cBuffer), defaultColor(defaultColor), recursionDepth(2)
{

}


void RayTracer::setCameraFrame(const dvec3& viewPosition, const dvec3& viewingDirection, dvec3 up)
{
	// TODO
	eye = viewPosition;

	w = glm::normalize(-viewingDirection);//backward
	u = glm::normalize(glm::cross(up, w));
	v = glm::normalize(glm::cross(w, u));
} // end setCameraFrame


void RayTracer::calculatePerspectiveViewingParameters(const double& verticalFieldOfViewDegrees)
{
	// TODO
	nx = (double)colorBuffer.getWindowWidth();
	ny = (double)colorBuffer.getWindowHeight();

	topLimit = 1.0;
	bottomLimit = -topLimit;

	distToPlane = topLimit / (glm::tan(glm::radians(verticalFieldOfViewDegrees) / 2.0));

	rightLimit = topLimit * (nx / ny);

	leftLimit = -rightLimit;

	renderPerspectiveView = true; // generate perspective view rays

} // end calculatePerspectiveViewingParameters


void RayTracer::calculateOrthographicViewingParameters(const double& viewPlaneHeight)
{
	topLimit = fabs(viewPlaneHeight) / 2.0;

	rightLimit = topLimit * ((double)colorBuffer.getWindowWidth() / colorBuffer.getWindowHeight()); // Set r based on aspect ratio and height of plane

	// Make view plane symetrical about the viewing direction
	leftLimit = -rightLimit;
	bottomLimit = -topLimit;

	// Calculate the distance between pixels in the horizontal and vertical directions
	nx = (double)colorBuffer.getWindowWidth();
	ny = (double)colorBuffer.getWindowHeight();

	distToPlane = 0.0; // Rays start on the view plane

	renderPerspectiveView = false; // generate orthographic view rays

} // end calculateOrthographicViewingParameters


void RayTracer::raytraceScene()
{
	// Iterate through each and every pixel in the rendering window
	// TODO
	Ray vr;
	for (int y = 0; y < colorBuffer.getWindowHeight(); y++) {
		for (int x = 0; x < colorBuffer.getWindowWidth(); x++) {

			if (renderPerspectiveView) {
				vr = getPerspectiveViewRay(x, y);
			}
			else {
				vr = getOrthoViewRay(x, y);
			}
			color vrColor = traceRay(vr, recursionDepth);
			colorBuffer.setPixel(x, y, vrColor);
		}
	}
} // end raytraceScene


color RayTracer::traceRay(const Ray& ray, int recursionLevel)
{
	// Find surface intersection that is closest to the origin of the viewRay
	// TODO
	HitRecord closesHit = findClosestIntersection(ray);

	//check if an intersection occurred
	if (closesHit.t < INFINITY) {

		color totalColor = closesHit.material.getEmisive();

		for (auto& light : lights) {

			//double d = light->getLightDistance(closesHit.interceptPoint);

			//dvec3 shadowFeeler = light->getLightVector(closesHit.interceptPoint);

			//HitRecord shadowHit = findClosestIntersection(Ray(closesHit.interceptPoint, shadowFeeler));

			//double attenuation = 0;

			
			//if (shadowFeeler != dvec3(0.0, 0.0, 0.0)) {
				totalColor += light->getLocalIllumination(-ray.direct, closesHit.interceptPoint,
					closesHit.surfaceNormal, closesHit.material, closesHit.uv);
			//}

		}

		//dvec3 reflectDirection = glm::reflect(ray.direct, closesHit.surfaceNormal);

		//Ray reflectRay(closesHit.interceptPoint + EPSILON * closesHit.surfaceNormal, reflectDirection);

		//totalColor += traceRay(reflectRay, recursionLevel - 1);

		return totalColor;
		//return closesHit.material.getDiffuse();
	}
	else {
		return defaultColor;
	}

} // end traceRay





HitRecord RayTracer::findClosestIntersection(const Ray& ray)
{
	HitRecord closestHit;
	closestHit.t = INFINITY;

	// Check if the ray intersects any surfaces in the scene
	// TODO
	for (auto& surfaces : this->surfaces) {
		HitRecord temp = surfaces->findIntersect(ray);
		if (temp.t < closestHit.t) {
			closestHit = temp;
		}
	}
	return closestHit;

} // end findIntersection


Ray RayTracer::getOrthoViewRay(const int& x, const int& y)
{
	Ray orthoViewRay;

	dvec2 uv = getImagePlaneCoordinates(x, y);

	orthoViewRay.origin = eye + uv.x * u + uv.y * v;
	orthoViewRay.direct = glm::normalize(-w);

	return orthoViewRay;

} // end getOrthoViewRay


Ray RayTracer::getPerspectiveViewRay(const int& x, const int& y)
{
	Ray perspectiveViewRay;

	// TODO
	perspectiveViewRay.origin = eye;

	dvec2 uv = getImagePlaneCoordinates(x, y);

	perspectiveViewRay.direct = glm::normalize(distToPlane * (-w) + uv.x * u + uv.y * v);

	return perspectiveViewRay;

} // end getPerspectiveViewRay


dvec2 RayTracer::getImagePlaneCoordinates(const int& x, const int& y)
{
	dvec2 s;

	// TODO
	s.x = (x + 0.5) * ((rightLimit - leftLimit) / nx) + leftLimit;
	s.y = (y + 0.5) * ((topLimit - bottomLimit) / ny) + bottomLimit;


	return s;

} // end getImagePlaneCoordinates





