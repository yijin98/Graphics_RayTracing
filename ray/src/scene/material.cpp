#include "material.h"
#include "../ui/TraceUI.h"
#include "light.h"
#include "ray.h"
extern TraceUI* traceUI;

#include <glm/gtx/io.hpp>
#include <iostream>
#include "../fileio/images.h"

using namespace std;
extern bool debugMode;

Material::~Material()
{
}

// Apply the phong model to this point on the surface of the object, returning
// the color of that point.
glm::dvec3 Material::shade(Scene* scene, const ray& r, const isect& i) const
{
	// YOUR CODE HERE

	// For now, this method just returns the diffuse color of the object.
	// This gives a single matte color for every distinct surface in the
	// scene, and that's it.  Simple, but enough to get you started.
	// (It's also inconsistent with the phong model...)

	// Your mission is to fill in this method with the rest of the phong
	// shading model, including the contributions of all the light sources.
	// You will need to call both distanceAttenuation() and
	// shadowAttenuation()
	// somewhere in your code in order to compute shadows and light falloff.
	//	if( debugMode )
	//		std::cout << "Debugging Phong code..." << std::endl;

	// When you're iterating through the lights,
	// you'll want to use code that looks something
	// like this:
	//
	// for ( const auto& pLight : scene->getAllLights() )
	// {
	//              // pLight has type unique_ptr<Light>
	// 		.
	// 		.
	// 		.
	// }
	glm::dvec3 color = ke(i) + ka(i) * scene->ambient();
	glm::dvec3 n = i.getN();
	for ( const auto& pLight : scene->getAllLights() )
	{
		glm::dvec3 atten = pLight->distanceAttenuation(r.at(i)) * pLight->shadowAttenuation(r, r.at(i));
		glm::dvec3 l = pLight->getDirection(r.at(i));
		double ln = max(glm::dot(l, n), 0.0);
		double vr = pow(max(glm::dot(-r.getDirection(), 2 * glm::dot(l, n) * n - l), 0.0), shininess(i));
		color += (kd(i) * ln + ks(i) * vr) * atten * pLight->getColor();
	}
	
	return color;
}

TextureMap::TextureMap(string filename)
{
	data = readImage(filename.c_str(), width, height);
	if (data.empty()) {
		width = 0;
		height = 0;
		string error("Unable to load texture map '");
		error.append(filename);
		error.append("'.");
		throw TextureMapException(error);
	}
}

glm::dvec3 TextureMap::getMappedValue(const glm::dvec2& coord) const
{
	// YOUR CODE HERE
	//
	// In order to add texture mapping support to the
	// raytracer, you need to implement this function.
	// What this function should do is convert from
	// parametric space which is the unit square
	// [0, 1] x [0, 1] in 2-space to bitmap coordinates,
	// and use these to perform bilinear interpolation
	// of the values.
	double x = coord[0] * double(width - 1);
	double y = coord[1] * double(height - 1);

	double xup = double(int(x) + 1) - x;
	double xdown = x - double(int(x));
	double yup = double(int(y) + 1) - y;
	double ydown = y - double(int(y));

	glm::dvec3 c11 = getPixelAt(int(x), int(y));
	glm::dvec3 c12 = getPixelAt(int(x), int(y) + 1);
	glm::dvec3 c21 = getPixelAt(int(x) + 1, int(y));
	glm::dvec3 c22 = getPixelAt(int(x) + 1, int(y) + 1);
	glm::dvec3 color = c11 * (xup) * (yup) + c21 * (xdown) * (yup) +
							c12 * (xup) * (ydown) + c22 * (xdown) * (ydown);

	return color;
}

glm::dvec3 TextureMap::getPixelAt(int x, int y) const
{
	// YOUR CODE HERE
	//
	// In order to add texture mapping support to the
	// raytracer, you need to implement this function.
	glm::dvec3 color = glm::dvec3(0,0,0);
	if( x < 0 || y < 0 || x >= width || y >= height || data.size() < 3 * width * height)
		return color;
	int pad = x + y * width;
	for(int i = 0; i < 3; i++)
		color[i] = double(data[i + pad * 3]) / 255.0;

	return color;



	// return glm::dvec3(1, 1, 1);
}

glm::dvec3 MaterialParameter::value(const isect& is) const
{
	if (0 != _textureMap)
		return _textureMap->getMappedValue(is.getUVCoordinates());
	else
		return _value;
}

double MaterialParameter::intensityValue(const isect& is) const
{
	if (0 != _textureMap) {
		glm::dvec3 value(
		        _textureMap->getMappedValue(is.getUVCoordinates()));
		return (0.299 * value[0]) + (0.587 * value[1]) +
		       (0.114 * value[2]);
	} else
		return (0.299 * _value[0]) + (0.587 * _value[1]) +
		       (0.114 * _value[2]);
}
