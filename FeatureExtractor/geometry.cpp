#include "geometry.h"

Geometry::Geometry()
{

}

Geometry::~Geometry()
{

}

float Geometry::EuclideanDistance(nite::Point3f& p1, nite::Point3f& p2)
{
	float result;
	result = std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z));
	return result;
}

nite::Point3f Geometry::CentroidOfJoints(nite::Skeleton skel, std::vector<nite::JointType> joints)
{
	nite::Point3f point_result(0, 0, 0);
	for each (nite::JointType joint in joints)
	{
		nite::Point3f pos = skel.getJoint(joint).getPosition();
		point_result.x += pos.x;
		point_result.y += pos.y;
		point_result.z += pos.z;
	}
	point_result.x /= joints.size();
	point_result.y /= joints.size();
	point_result.z /= joints.size();
	return point_result;
}




