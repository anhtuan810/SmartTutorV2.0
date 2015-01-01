#ifndef POINT3D_H
#define POINT3D_H

#include "NiTE.h"

class Point3D
{
public:
	float X;
	float Y;
	float Z;

	Point3D();
	Point3D(float x, float y, float z);
	Point3D(nite::Point3f position);
	~Point3D();

protected:


private:

};


#endif