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

	for (size_t i = 0; i < 100; i++)
	{
		sensor_reader.QueryFrame();
		feature_extractor.ProcessNewSample(sensor_reader);
		overall_assessment.AssessOneFeatureSet(feature_extractor);
		std::cout << i << " - " << overall_assessment.GetScoreSeries_Direction().size() << "\n";
	}
	std::cin.get();
}