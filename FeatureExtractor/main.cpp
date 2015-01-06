#include "sensor_reader.h"
#include "geometry.h"
#include "feature_extractor.h"
#include <iostream>

void main()
{
	Sensor_Reader sensor_reader;
	sensor_reader.TurnOnOrDie("F:\\Development of SmartTutor\\11.oni");
	FeatureExtractor feature_extractor;
	for (size_t i = 0; i < 100; i++)
	{
		sensor_reader.QueryFrame();
		feature_extractor.ProcessNewSample(sensor_reader);
	}

	

	std::cin.get();
}