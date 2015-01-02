#include "sensor_reader.h"
#include "geometry.h"
#include "feature_extractor.h"
#include <iostream>

void main()
{
	SensorReader sensor_reader("F:\\Development of SmartTutor\\11.oni");
	sensor_reader.TurnOnSensor();
	FeatureExtractor feature_extractor;
	for (size_t i = 0; i < 100; i++)
	{
		sensor_reader.QuerrySensor();
		feature_extractor.ProcessNewSample(sensor_reader);
	}

	
	std::cin.get();
}