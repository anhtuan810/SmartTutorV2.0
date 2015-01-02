#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "sensor_reader.h"

class Geometry
{
public:
	Geometry();
	~Geometry();

	float EuclideanDistance(nite::Point3f& p1, nite::Point3f& p2);
	nite::Point3f CentroidOfJoints(nite::Skeleton skel, std::vector<nite::JointType> joints);

protected:

private:

};

#endif