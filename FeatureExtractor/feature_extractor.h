#ifndef FEATURE_EXTRACTOR_H
#define FEATURE_EXTRACTOR_H

#include "sensor_reader.h"
#include "geometry.h"
#include <vector>

class FeatureExtractor
{
public:
	FeatureExtractor();
	~FeatureExtractor();
	void ProcessNewSample(SensorReader& sensor_reader);
	std::vector<float> GetVelocity_LeftHand();
	std::vector<float> GetVelocity_RightHand();
	std::vector<float> GetDisplacement_Feet();
	std::vector<float> GetEnergy();
	std::vector<float> GetFootStretch();
	std::vector<float> GetBalanceBackForth();
	std::vector<float> GetBalanceLeftRight();

protected:

private:
	Geometry geometry_;
	const int BUFFER_SIZE = 100;

	std::vector<float> f_velocity_left_hand_;
	std::vector<float> f_velocity_right_hand_;	
	std::vector<float> f_velocity_global_;
	std::vector<float> f_velocity_feet_;
	std::vector<float> f_energy_;

	std::vector<float> f_balance_left_right_;
	std::vector<float> f_balance_back_forth_;
	std::vector<float> f_foot_stretch_;

	void CheckBufferSize_(std::vector<float>& buffer, int size);
};

#endif