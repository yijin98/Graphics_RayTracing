#include "cubeMap.h"
#include "ray.h"
#include "../ui/TraceUI.h"
#include "../scene/material.h"
#include <iostream>

using namespace std;
extern TraceUI* traceUI;

glm::dvec3 CubeMap::getColor(ray r) const
{
	// YOUR CODE HERE
	// FIXME: Implement Cube Map here
	glm::dvec3 d = r.getDirection();
	double absd[] = {fabs(d[0]), fabs(d[1]), fabs(d[2])};
	double* max = std::max_element(absd, absd + 3);
	int faceNum;
	double u, v;
	if (*max == absd[0]){
		u = d[2];
		v = d[1];
		faceNum = 1;
		if (d[0] > 0){ 
			u = -u;
			faceNum = 0;
		}
	} else if (*max == absd[1]){
		u = d[0];
		v = d[2];
		faceNum = 3;
		if (d[1] > 0){ 
			v = -v;
			faceNum = 2;
		}
	} else if (*max == absd[2]){
		u = d[0];
		v = d[1];
		faceNum = 5;
		if (d[2] > 0){ 
			u = -u;
			faceNum = 4;
		}
	}
	u = (u / *max + 1.0) / 2.0;
	v = (v / *max + 1.0) / 2.0;
	return tMap[faceNum]->getMappedValue(glm::dvec2(u, v));
}

CubeMap::CubeMap()
{
}

CubeMap::~CubeMap()
{
}

void CubeMap::setNthMap(int n, TextureMap* m)
{
	if (m != tMap[n].get())
		tMap[n].reset(m);
}
