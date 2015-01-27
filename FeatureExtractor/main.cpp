#include "sensor_reader.h"
#include "geometry.h"
#include "feature_extractor.h"
#include <iostream>

void main()
{
	Sensor_Reader sensor_reader;
	sensor_reader.TurnOnOrDie("G:\\Development of SmartTutor\\11.oni");
	FeatureExtractor feature_extractor;
	int i = 0;
	while (true)
	{
		sensor_reader.QueryFrame();
		feature_extractor.ProcessNewSample(sensor_reader);
		std::cout << feature_extractor.GetStability().size() << "\n";
	}

	std::cin.get();
}