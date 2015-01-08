#include "sensor_reader.h"
#include "feature_extractor.h"
#include "overall_assessment.h"
#include <iostream>


void main()
{
	Sensor_Reader sensor_reader;
	sensor_reader.TurnOnOrDie("G:\\Development of SmartTutor\\11.oni");
	FeatureExtractor feature_extractor;
	OverallAssessment overall_assessment;

	int i = 0;
	while (true)
	{
		sensor_reader.QueryFrame();
		feature_extractor.ProcessNewSample(sensor_reader);
		overall_assessment.AssessOneFeatureSet(feature_extractor);
		std::cout << i++ << " - " << overall_assessment.GetScoreSeries_Direction().size() << "\n";
	}
	std::cin.get();
}