#include <cmath>
#include <iostream>

#include "light.h"
#include <glm/glm.hpp>
#include <glm/gtx/io.hpp>


using namespace std;

double DirectionalLight::distanceAttenuation(const glm::dvec3& P) const
{
	// distance to light is infinite, so f(di) goes to 0.  Return 1.
	return 1.0;
}


glm::dvec3 DirectionalLight::shadowAttenuation(const ray& r, const glm::dvec3& p) const
{
	// YOUR CODE HERE:
	// You should implement shadow-handling code here.

	ray sRay = ray(p, getDirection(p), glm::dvec3(1,1,1), ray::SHADOW);
	isect is;
	while(scene->intersect(sRay, is)){
		if (!is.getMaterial().Trans()){
			return glm::dvec3(0.0, 0.0, 0.0);
		}
		return glm::dvec3(1.0, 1.0, 1.0);
	}

	return glm::dvec3(1.0, 1.0, 1.0);
	
}

glm::dvec3 DirectionalLight::getColor() const
{
	return color;
}

glm::dvec3 DirectionalLight::getDirection(const glm::dvec3& P) const
{
	return -orientation;	
}

double PointLight::distanceAttenuation(const glm::dvec3& P) const
{

	// YOUR CODE HERE

	// You'll need to modify this method to attenuate the intensity 
	// of the light based on the distance between the source and the 
	// point P.  For now, we assume no attenuation and just return 1.0
	double dis = glm::distance(position, P);
	double inten = 1 / (constantTerm + linearTerm * dis + quadraticTerm * dis * dis);
	return min(1.0, inten);
}

glm::dvec3 PointLight::getColor() const
{
	return color;
}

glm::dvec3 PointLight::getDirection(const glm::dvec3& P) const
{
	return glm::normalize(position - P);
}


glm::dvec3 PointLight::shadowAttenuation(const ray& r, const glm::dvec3& p) const
{
	// YOUR CODE HERE:
	// You should implement shadow-handling code here.
	
	ray sRay = ray(p, getDirection(p), glm::dvec3(1,1,1), ray::SHADOW);
	isect is;
	while(scene->intersect(sRay,is)){
		glm::dvec3 pos = sRay.at(is);
		if (glm::dot(pos - p, pos - position) > 0)
			return glm::dvec3(1.0,1.0,1.0);
		else
			return glm::dvec3(0.0,0.0,0.0);
	}
	

	return glm::dvec3(1,1,1);
}

#define VERBOSE 0

