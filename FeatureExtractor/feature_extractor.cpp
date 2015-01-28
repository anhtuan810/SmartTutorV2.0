//
//  Smart Tutor v2.0
//	FeatureExtractor: Extract features from skeletons
//
//  Created: 2015.01.02
//	2015.01.10: Update, improve accuracy
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#include "feature_extractor.h"
#include <algorithm>

using namespace openni;
using namespace nite;

FeatureExtractor::FeatureExtractor(Sensor_Reader &sensor_reader)
{
	sensor_reader_ = &sensor_reader;
}

FeatureExtractor::~FeatureExtractor(){}


//////////////////////////////////////////////////////////////////////////
#pragma region Getters

int FeatureExtractor::GetActualBufferSize()
{
	return f_balance_left_right_.size();
}

std::vector<float> FeatureExtractor::GetVelocity_LeftHand()
{
	//return post_processing_.SmoothByAveraging(f_velocity_left_hand_);
	return post_processing_.SmoothByAveraging(f_velocity_left_hand_);
}

std::vector<float> FeatureExtractor::GetVelocity_RightHand()
{
	return post_processing_.SmoothByAveraging(f_velocity_right_hand_);
	//return f_velocity_right_hand_smooth_;
}

std::vector<float> FeatureExtractor::GetVelocity_Foot()
{
	return post_processing_.SmoothByAveraging(f_velocity_foot_);
	//return f_velocity_foot_smooth_;
}

std::vector<float> FeatureExtractor::GetVelocity_Global()
{
	return post_processing_.SmoothByAveraging(f_velocity_global_);
	//return f_velocity_global_smooth_;
}

std::vector<float> FeatureExtractor::GetDirection_BackForth()
{
	return post_processing_.SmoothByAveraging(f_direction_back_forth_);
	//return f_direction_back_forth_smooth_;
}

std::vector<float> FeatureExtractor::GetEnergy()
{
	return post_processing_.SmoothByAveraging(f_energy_);
	//return f_energy_smooth_;
}

std::vector<float> FeatureExtractor::GetFootStretch()
{
	return post_processing_.SmoothByAveraging(f_foot_stretch_);
	//return f_foot_stretch_smooth_;
}

std::vector<float> FeatureExtractor::GetBalanceBackForth()
{
	return post_processing_.SmoothByAveraging(f_balance_back_forth_);
	//return f_balance_back_forth_smooth_;
}

std::vector<float> FeatureExtractor::GetBalanceLeftRight()
{
	return post_processing_.SmoothByAveraging(f_balance_left_right_);
	//return f_balance_left_right_smooth_;
}

std::vector<float> FeatureExtractor::GetStability()
{
	return post_processing_.SmoothByAveraging(f_stability_);
}

std::vector<float> FeatureExtractor::GetOpenness()
{
	return post_processing_.SmoothByAveraging(f_openness_);
}

std::vector<float> FeatureExtractor::GetImpulsiveness()
{
	return f_impulsiveness_;
}

std::vector<float> FeatureExtractor::GetVelocity_Hands()
{
	return post_processing_.SmoothByAveraging(f_velocity_hands_);
}

#pragma endregion
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
#pragma region Extract Features

void FeatureExtractor::Reset()
{
	f_velocity_left_hand_.clear();
	f_velocity_right_hand_.clear();
	f_velocity_hands_.clear();
	f_velocity_global_.clear();
	f_velocity_foot_.clear();

	f_energy_.clear();
	f_impulsiveness_.clear();
	f_direction_back_forth_.clear();

	f_balance_left_right_.clear();
	f_balance_back_forth_.clear();
	f_stability_.clear();
	f_foot_stretch_.clear();
	f_openness_.clear();
}

void FeatureExtractor::ProcessNewSample()
{
	if (sensor_reader_->GetActualBufferSize() < 2)
		return;

	latest_sample_ = sensor_reader_->GetLatestSample();
	second_sample_ = sensor_reader_->GetSecondLatestSample();

	//
	//	Get all of features
	//
	GetF_HandVelocity_();
	GetF_FeetVelocity_();
	GetF_Energy_();
	GetF_Impulsiveness_(); // Only after Get Energy
	GetF_Direction_BackForth_();
	GetF_GlobalVelocity_();
	GetF_FeetStretch_();
	GetF_BalanceBackForth_();
	GetF_BalanceLeftRight_();
	GetF_Stability_(); // Only after Get Balance
	GetF_Openness_();

	//
	// Final check
	//
	if (!latest_sample_.IsContainUser || !second_sample_.IsContainUser)
	{
		f_velocity_left_hand_.at(f_velocity_left_hand_.size() - 1) = 0;
		f_velocity_right_hand_.at(f_velocity_right_hand_.size() - 1) = 0;
		f_velocity_hands_.at(f_velocity_hands_.size() - 1) = 0;
		f_velocity_foot_.at(f_velocity_foot_.size() - 1) = 0;
		f_energy_.at(f_energy_.size() - 1) = 0;
		f_direction_back_forth_.at(f_direction_back_forth_.size() - 1) = 0;
		f_foot_stretch_.at(f_foot_stretch_.size() - 1) = 0;
		f_balance_back_forth_.at(f_balance_back_forth_.size() - 1) = 0;
		f_balance_left_right_.at(f_balance_left_right_.size() - 1) = 0;
		f_velocity_global_.at(f_velocity_global_.size() - 1) = 0;
		f_openness_.at(f_openness_.size() - 1) = 0;
		f_stability_.at(f_stability_.size() - 1) = 0;
	}
}

void FeatureExtractor::GetF_HandVelocity_()
{
	float velocity_left_hand = GetJointDisplacement_Shifted_(JOINT_LEFT_HAND, JOINT_LEFT_SHOULDER);
	float velocity_right_hand = GetJointDisplacement_Shifted_(JOINT_RIGHT_HAND, JOINT_RIGHT_SHOULDER);
	f_velocity_left_hand_.push_back(velocity_left_hand);
	f_velocity_right_hand_.push_back(velocity_right_hand);
	f_velocity_hands_.push_back(velocity_left_hand + velocity_right_hand);
	CheckBufferSize_(f_velocity_left_hand_, FEATURE_BUFF_SZ_VELOCITY_LEFT_HAND);
	CheckBufferSize_(f_velocity_right_hand_, FEATURE_BUFF_SZ_VELOCITY_RIGHT_HAND);
	CheckBufferSize_(f_velocity_hands_, FEATURE_BUFF_SZ_VELOCITY_HANDS);	
}

void FeatureExtractor::GetF_GlobalVelocity_()
{
	std::vector<nite::JointType> centroid_joints;
	centroid_joints.push_back(nite::JOINT_HEAD);
	centroid_joints.push_back(nite::JOINT_NECK);
	centroid_joints.push_back(nite::JOINT_LEFT_HAND);
	centroid_joints.push_back(nite::JOINT_RIGHT_HAND);
	centroid_joints.push_back(nite::JOINT_TORSO);
	centroid_joints.push_back(nite::JOINT_LEFT_FOOT);
	centroid_joints.push_back(nite::JOINT_RIGHT_FOOT);
	nite::Point3f centroid_latest = geometry_.CentroidOfJoints(latest_sample_.GetSkeleton(), centroid_joints);
	nite::Point3f centroid_second = geometry_.CentroidOfJoints(second_sample_.GetSkeleton(), centroid_joints);
	float velocity_global = geometry_.EuclideanDistance(centroid_latest, centroid_second);
	f_velocity_global_.push_back(velocity_global);
	CheckBufferSize_(f_velocity_global_, FEATURE_BUFF_SZ_VELOCITY_GLOBAL);
}

void FeatureExtractor::GetF_FeetVelocity_()
{
	std::vector<nite::JointType> feet_joints;
	feet_joints.push_back(nite::JOINT_LEFT_FOOT);
	feet_joints.push_back(nite::JOINT_RIGHT_FOOT);
	nite::Point3f pos_feet_1 = geometry_.CentroidOfJoints(latest_sample_.GetSkeleton(), feet_joints);
	nite::Point3f pos_feet_2 = geometry_.CentroidOfJoints(second_sample_.GetSkeleton(), feet_joints);
	float displacement_foot = geometry_.EuclideanDistance(pos_feet_1, pos_feet_2);
	f_velocity_foot_.push_back(displacement_foot);
	CheckBufferSize_(f_velocity_foot_, FEATURE_BUFF_SZ_VELOCITY_FOOT);
}

void FeatureExtractor::GetF_Energy_()
{
	// 1- Compute velocity of joints
	//
	float velocity_head = GetJointDisplacement_(JOINT_HEAD);
	float velocity_neck = GetJointDisplacement_(JOINT_NECK);
	float velocity_left_elbow = GetJointDisplacement_(JOINT_LEFT_ELBOW);
	float velocity_right_elbow = GetJointDisplacement_(JOINT_RIGHT_ELBOW);
	float velocity_torso = GetJointDisplacement_(JOINT_TORSO);
	float velocity_left_shoulder = GetJointDisplacement_(JOINT_LEFT_SHOULDER);
	float velocity_right_shoulder = GetJointDisplacement_(JOINT_RIGHT_SHOULDER);
	float velocity_left_hand = GetJointDisplacement_(JOINT_LEFT_HAND);
	float velocity_right_hand = GetJointDisplacement_(JOINT_RIGHT_HAND);
	float velocity_left_hip = GetJointDisplacement_(JOINT_LEFT_HIP);
	float velocity_right_hip = GetJointDisplacement_(JOINT_RIGHT_HIP);
	float velocity_left_knee = GetJointDisplacement_(JOINT_LEFT_KNEE);
	float velocity_right_knee = GetJointDisplacement_(JOINT_RIGHT_KNEE);
	float velocity_left_foot = GetJointDisplacement_(JOINT_LEFT_FOOT);
	float velocity_right_foot = GetJointDisplacement_(JOINT_RIGHT_FOOT);
	//
	// 2 - Velocity of combined joints
	//
	std::vector<nite::JointType> head_neck_joints;
	head_neck_joints.push_back(nite::JOINT_HEAD);
	head_neck_joints.push_back(nite::JOINT_NECK);
	nite::Point3f pos_head_neck_1 = geometry_.CentroidOfJoints(latest_sample_.GetSkeleton(), head_neck_joints);
	nite::Point3f pos_head_neck_2 = geometry_.CentroidOfJoints(second_sample_.GetSkeleton(), head_neck_joints);
	float velocity_head_neck = geometry_.EuclideanDistance(pos_head_neck_1, pos_head_neck_2);

	std::vector<nite::JointType> torso_joints;
	torso_joints.push_back(nite::JOINT_TORSO);
	torso_joints.push_back(nite::JOINT_LEFT_SHOULDER);
	torso_joints.push_back(nite::JOINT_RIGHT_SHOULDER);
	nite::Point3f pos_torso_shoulders_1 = geometry_.CentroidOfJoints(latest_sample_.GetSkeleton(), torso_joints);
	nite::Point3f pos_torso_shoulders_2 = geometry_.CentroidOfJoints(second_sample_.GetSkeleton(), torso_joints);
	float velocity_torso_shoulders = geometry_.EuclideanDistance(pos_torso_shoulders_1, pos_torso_shoulders_2);

	std::vector<nite::JointType> hip_joints;
	hip_joints.push_back(nite::JOINT_LEFT_HIP);
	hip_joints.push_back(nite::JOINT_RIGHT_HIP);
	nite::Point3f pos_hip_1 = geometry_.CentroidOfJoints(latest_sample_.GetSkeleton(), hip_joints);
	nite::Point3f pos_hip_2 = geometry_.CentroidOfJoints(second_sample_.GetSkeleton(), hip_joints);
	float velocity_hips = geometry_.EuclideanDistance(pos_hip_1, pos_hip_2);

	//
	// 3 - Add the mass constants
	//
	float energy =
		velocity_head_neck * velocity_head_neck * 6.7 +
		velocity_left_elbow * velocity_left_elbow * 2.4 +
		velocity_right_elbow * velocity_right_elbow * 2.4 +
		velocity_left_hand * velocity_left_hand * 2.3 +
		velocity_right_hand * velocity_right_hand * 2.3 +
		velocity_torso_shoulders * velocity_torso_shoulders * 33.3 +
		velocity_hips * velocity_hips * 14.2 +
		velocity_left_knee * velocity_left_knee * 12.2 +
		velocity_right_knee * velocity_right_knee * 12.2 +
		velocity_left_foot * velocity_left_foot * 6 +
		velocity_right_foot * velocity_right_foot * 6;
	f_energy_.push_back(energy);
	CheckBufferSize_(f_energy_, FEATURE_BUFF_SZ_ENERGY);
}

void FeatureExtractor::GetF_Direction_BackForth_()
{
	// Compute amount of back-forth movement between 2 most recent frames
	// The accurate amount of back-forth displacement will be computed later on in the smoothing step
	//
	// Compute distance on the Oy axis
	//
	nite::Point3f p1 = latest_sample_.GetJointPosition(JOINT_TORSO);
	nite::Point3f p2 = second_sample_.GetJointPosition(JOINT_TORSO);
	float distance = p2.z - p1.z;
	f_direction_back_forth_.push_back(distance);
	CheckBufferSize_(f_direction_back_forth_, FEATURE_BUFF_SZ_DIRECTION);
}

void FeatureExtractor::GetF_FeetStretch_()
{
	float distance_shoulders = geometry_.EuclideanDistance(latest_sample_.GetJointPosition(nite::JOINT_LEFT_SHOULDER), latest_sample_.GetJointPosition(nite::JOINT_RIGHT_SHOULDER));
	float distance_foot = geometry_.EuclideanDistance(latest_sample_.GetJointPosition(nite::JOINT_LEFT_FOOT), latest_sample_.GetJointPosition(nite::JOINT_RIGHT_FOOT));
	float foot_stretch = distance_foot / distance_shoulders;
	f_foot_stretch_.push_back(foot_stretch);
	CheckBufferSize_(f_foot_stretch_, FEATURE_BUFF_SZ_FOOT_STRETCH);
}

void FeatureExtractor::GetF_BalanceBackForth_()
{
	std::vector<nite::JointType> foot_joints;
	foot_joints.push_back(nite::JOINT_LEFT_FOOT);
	foot_joints.push_back(nite::JOINT_RIGHT_FOOT);
	nite::Point3f foot_center = geometry_.CentroidOfJoints(latest_sample_.GetSkeleton(), foot_joints);

	std::vector<nite::JointType> shoulder_joints;
	shoulder_joints.push_back(nite::JOINT_LEFT_SHOULDER);
	shoulder_joints.push_back(nite::JOINT_RIGHT_SHOULDER);
	nite::Point3f shoulders_center = geometry_.CentroidOfJoints(latest_sample_.GetSkeleton(), shoulder_joints);

	// Project to the ground plane
	foot_center.y = 0;
	shoulders_center.y = 0;
	float leaning_back_forth = geometry_.EuclideanDistance(foot_center, shoulders_center);

	// The sign depend on which side Shoulders_Center compare to the line created by Foot positions
	nite::Point3f foot_left = latest_sample_.GetJointPosition(JOINT_LEFT_FOOT);
	nite::Point3f foot_right = latest_sample_.GetJointPosition(JOINT_RIGHT_FOOT);
	
	float sign = geometry_.Position_Point_Line(foot_left.x, foot_left.z, foot_right.x, foot_right.z, shoulders_center.x, shoulders_center.z);
	leaning_back_forth *= sign;
	f_balance_back_forth_.push_back(leaning_back_forth);
	CheckBufferSize_(f_balance_back_forth_, FEATURE_BUFF_SZ_BALANCE_BACK_FORTH);
}

void FeatureExtractor::GetF_BalanceLeftRight_()
{
	nite::Point3f foot_left_2d = latest_sample_.GetJointPosition(nite::JOINT_LEFT_FOOT);
	foot_left_2d.y = 0;
	nite::Point3f foot_right_2d = latest_sample_.GetJointPosition(nite::JOINT_RIGHT_FOOT);
	foot_right_2d.y = 0;
	nite::Point3f torso_2d = latest_sample_.GetJointPosition(nite::JOINT_TORSO);
	torso_2d.y = 0;

	float distance_left = geometry_.EuclideanDistance(torso_2d, foot_left_2d);
	float distance_right = geometry_.EuclideanDistance(torso_2d, foot_right_2d);
	float leaning_left_right = distance_left - distance_right;

	f_balance_left_right_.push_back(leaning_left_right);
	CheckBufferSize_(f_balance_left_right_, FEATURE_BUFF_SZ_BALANCE_LEFT_RIGHT);
}

void FeatureExtractor::GetF_Openness_()
{
	//
	// Get size of bounding cube of several points, by getting min and max on 3 axes
	//
    std::pair<float, float> minmax_X = std::minmax({ 
		latest_sample_.GetJointPosition(JOINT_HEAD).x,
		latest_sample_.GetJointPosition(JOINT_LEFT_HAND).x,
		latest_sample_.GetJointPosition(JOINT_RIGHT_HAND).x,
		latest_sample_.GetJointPosition(JOINT_TORSO).x,
		latest_sample_.GetJointPosition(JOINT_LEFT_FOOT).x,
		latest_sample_.GetJointPosition(JOINT_RIGHT_FOOT).x });

	std::pair<float, float> minmax_Y = std::minmax({ 
		latest_sample_.GetJointPosition(JOINT_HEAD).y,
		latest_sample_.GetJointPosition(JOINT_LEFT_HAND).y,
		latest_sample_.GetJointPosition(JOINT_RIGHT_HAND).y,
		latest_sample_.GetJointPosition(JOINT_TORSO).y,
		latest_sample_.GetJointPosition(JOINT_LEFT_FOOT).y,
		latest_sample_.GetJointPosition(JOINT_RIGHT_FOOT).y });

	std::pair<float, float> minmax_Z = std::minmax({ 
		latest_sample_.GetJointPosition(JOINT_HEAD).z,
		latest_sample_.GetJointPosition(JOINT_LEFT_HAND).z,
		latest_sample_.GetJointPosition(JOINT_RIGHT_HAND).z,
		latest_sample_.GetJointPosition(JOINT_TORSO).z,
		latest_sample_.GetJointPosition(JOINT_LEFT_FOOT).z,
		latest_sample_.GetJointPosition(JOINT_RIGHT_FOOT).z });

	float sz_X = minmax_X.second - minmax_X.first;
	float sz_Y = minmax_Y.second - minmax_Y.first;
	float sz_Z = minmax_Z.second - minmax_Z.first;

	//
	//	Normalize by the height of user
	//
	float height = latest_sample_.GetJointPosition(JOINT_HEAD).y;
	float openness = (sz_X * sz_Y * sz_Z) / height;

	f_openness_.push_back(openness);
	CheckBufferSize_(f_openness_, FEATURE_BUFF_SZ_OPENNESS);
}

void FeatureExtractor::GetF_Impulsiveness_()
{
	f_impulsiveness_.clear();
	for (size_t i = 0; i < f_energy_.size(); i++)
	{
		f_impulsiveness_.push_back(0);
	}

	// The constants
	const int kThresQoM = 200000;
	const int kPeriodMin = 3;
	const int kPeriodMax = 50;

	int i = 0;
	while (i < f_energy_.size() - 1)
	{
		float energy = f_energy_[i];
		if (energy > kThresQoM)
		{
			int id_start = i;
			while (f_energy_[i] > kThresQoM)
				i++;
			int id_end = i - 1;

			if (id_end - id_start + 1 > kPeriodMin && id_end - id_start + 1 < kPeriodMax)
			{
				// If contain impulse between id_min and id_max ==> Change values
				float sum = 0;
				for (size_t k = id_start; k <= id_end; k++)
				{
					sum += f_energy_[k];
				}
				float impulse = sum / (id_end - id_start + 1);

				// Assign new value
				for (size_t k = id_start; k <= id_end; k++)
				{
					f_impulsiveness_[k] = impulse;
				}
			}
		}
		i++;
	}
}

void FeatureExtractor::GetF_Stability_()
{
	if (f_balance_left_right_.size() == 0)
		return;

	if (f_balance_left_right_.size() == 1)
	{
		f_stability_.push_back(0);
		return;
	}

	// Only process the last sample of balance features
	int sz = f_balance_left_right_.size();
	float stability_leftright = std::abs(f_balance_left_right_[sz - 1] - f_balance_left_right_[sz - 2]);
	float stability_backforth = std::abs(f_balance_back_forth_[sz - 1] - f_balance_back_forth_[sz - 2]);

	// Normally, balance back forth is less than balance left right
	f_stability_.push_back(stability_leftright + stability_backforth * 2);
	CheckBufferSize_(f_stability_, FEATURE_BUFF_SZ_OPENNESS);
}

#pragma endregion
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
#pragma region Supportive Functions

void FeatureExtractor::CheckBufferSize_(std::vector<float>& buffer, int size)
{
	if (buffer.size() > size)
		buffer.erase(buffer.begin());
}

float FeatureExtractor::GetJointDisplacement_(nite::JointType joint)
{
	Point3f point_latest = latest_sample_.GetJointPosition(joint);
	Point3f point_second = second_sample_.GetJointPosition(joint);
	return geometry_.EuclideanDistance(point_latest, point_second);
}

//	Shift the whole skeleton based on a reference point 
float FeatureExtractor::GetJointDisplacement_Shifted_(nite::JointType joint, nite::JointType ref_joint)
{
	//
	// Displacement of reference point
	//
	Point3f ref_latest = latest_sample_.GetJointPosition(ref_joint);
	Point3f ref_second = second_sample_.GetJointPosition(ref_joint);
	Point3f ref_disp = Point3f(ref_second.x - ref_latest.x, ref_second.y - ref_latest.y, ref_second.z - ref_latest.z);
	//
	//	Shift the second point
	//
	Point3f point_latest = latest_sample_.GetJointPosition(joint);
	Point3f point_second = second_sample_.GetJointPosition(joint);
	point_second.x -= ref_disp.x;
	point_second.y -= ref_disp.y;
	point_second.z -= ref_disp.z;
	return geometry_.EuclideanDistance(point_latest, point_second);
}

#pragma endregion
//////////////////////////////////////////////////////////////////////////