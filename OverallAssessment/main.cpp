#include "sensor_reader.h"
#include "feature_extractor.h"
#include "overall_assessment.h"
#include <iostream>


void main()
{
	Sensor_Reader sensor_reader;
	sensor_reader.TurnOnOrDie("G:\\Development of SmartTutor\\11.oni");
	FeatureExtractor feature_extractor(sensor_reader);
	OverallAssessment overall_assessment(feature_extractor);

	int i = 0;
	while (true)
	{
		sensor_reader.QueryFrame();
		feature_extractor.ProcessNewSample();
		overall_assessment.PerformAssessment();
		std::cout << i++ << " - " << overall_assessment.GetBinarySeries_ByCodeword(Codeword::Energy_High).size() << "\n";
	}
	std::cin.get();
}