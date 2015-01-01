#include "point3d.h"

Point3D::Point3D()
{

}

Point3D::Point3D(float x, float y, float z)
{
	this->X = x;
	this->Y = y;
	this->Z = z;
}

Point3D::Point3D(nite::Point3f position)
{
	this->X = position.x;
	this->Y = position.y;
	this->Z = position.x;
}

Point3D::~Point3D()
{

}

