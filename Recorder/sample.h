#ifndef SENSOR_SAMPLE_H
#define SENSOR_SAMPLE_H


#include "point3d.h"
#include <NiTE.h>

class Sample
{
public:
	bool IsContainUser;

	Sample();
	Sample(nite::Skeleton& skel);
	~Sample();

	Point3D GetHead();
	Point3D GetNeck();
	Point3D GetLeft_Shoulder();
	Point3D GetRight_Shoulder();
	Point3D GetLeft_Elbow();
	Point3D GetRight_Elbow();
	Point3D GetLeft_Hand();
	Point3D GetRight_Hand();
	Point3D GetTorso();
	Point3D GetLeft_Hip();
	Point3D GetRight_Hip();
	Point3D GetLeft_Knee();
	Point3D GetRight_Knee();
	Point3D GetLeft_Foot();
	Point3D GetRight_Foot();

protected:

private:
	Point3D head_;
	Point3D neck_;
	Point3D left_shoulder_;
	Point3D right_shoulder_;
	Point3D left_elbow_;
	Point3D right_elbow_;
	Point3D left_hand_;
	Point3D right_hand_;
	Point3D torso_;
	Point3D left_hip_;
	Point3D right_hip_;
	Point3D left_knee_;
	Point3D right_knee_;
	Point3D left_foot_;
	Point3D right_foot_;
};

#endif