//
//  Smart Tutor v1.0
//	Recorder
//
//  Created: 
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//
#include "sensor_reader.h"
#include "iostream"
#include "sample.h"
#include "point3d.h"

void main()
{
	SensorReader reader("F:\\Development of SmartTutor\\11.oni");
	reader.TurnOnSensor();
	int i = 0;
	while(true)
	{
		reader.QuerrySensor();
		Sample sample = reader.GetLatestSample();
		if (sample.IsContainUser)
			std::cout << i++ << ": " << reader.GetLatestSample().GetLeft_Elbow().Y << "\n";
	}
	reader.TurnOffSensor();
	

	std::cin.get();
	return;
}