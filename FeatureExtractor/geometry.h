//
//  Smart Tutor v2.0
//	FeatureExtractor: Extract features from skeletons
//
//  Created: 2015.01.02
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "sensor_reader.h"

class Geometry
{
public:
	Geometry();
	~Geometry();

	float EuclideanDistance(nite::Point3f& p1, nite::Point3f& p2);
	nite::Point3f CentroidOfJoints(nite::Skeleton skel, std::vector<nite::JointType> joints);

private:
};

#endif