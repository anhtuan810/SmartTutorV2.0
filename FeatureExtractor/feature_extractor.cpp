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

using namespace openni;
using namespace nite;

FeatureExtractor::FeatureExtractor(){}

FeatureExtractor::~FeatureExtractor(){}


//////////////////////////////////////////////////////////////////////////
#pragma region Getters

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

#pragma endregion


//////////////////////////////////////////////////////////////////////////
//Directly send the whole Sensor_Reader object, with all buffer to the processor
#pragma region Extract Features

void FeatureExtractor::ProcessNewSample(Sensor_Reader& sensor_reader)
{
	if (sensor_reader.GetActualBufferSize() < 2)
		return;

	Sample sample_latest = sensor_reader.GetLatestSample();
	Sample sample_second = sensor_reader.GetSecondLatestSample();

	GetF_HandVelocity_(sample_latest, sample_second);
	GetF_FeetVelocity_(sample_latest, sample_second);
	GetF_Energy_(sample_latest, sample_second);
	GetF_Direction_BackForth_(sample_latest, sample_second);
	GetF_GlobalVelocity_(sample_latest, sample_second);
	GetF_FeetStretch_(sample_latest);
	GetF_BalanceBackForth_(sample_latest);
	GetF_BalanceLeftRight_(sample_latest);
	//
	// Final check
	//
	if (!sample_latest.IsContainUser || !sample_second.IsContainUser)
	{
		f_velocity_left_hand_.at(f_velocity_left_hand_.size() - 1) = 0;
		f_velocity_right_hand_.at(f_velocity_right_hand_.size() - 1) = 0;
		f_velocity_foot_.at(f_velocity_foot_.size() - 1) = 0;
		f_energy_.at(f_energy_.size() - 1) = 0;
		f_direction_back_forth_.at(f_direction_back_forth_.size() - 1) = 0;
		f_foot_stretch_.at(f_foot_stretch_.size() - 1) = 0;
		f_balance_back_forth_.at(f_balance_back_forth_.size() - 1) = 0;
		f_balance_left_right_.at(f_balance_left_right_.size() - 1) = 0;
		f_velocity_global_.at(f_velocity_global_.size() - 1) = 0;
	}
	//
	//	Smoothing
	//
	//f_velocity_left_hand_smooth_ = post_processing_.SmoothByAveraging(f_velocity_left_hand_);
	//f_velocity_right_hand_smooth_ = post_processing_.SmoothByAveraging(f_velocity_right_hand_);
	//f_velocity_foot_smooth_ = post_processing_.SmoothByAveraging(f_velocity_foot_);
	//f_energy_smooth_ = post_processing_.SmoothByAveraging(f_energy_);
	//f_direction_back_forth_smooth_ = post_processing_.SmoothByAveraging(f_direction_back_forth_);
	//f_foot_stretch_smooth_ = post_processing_.SmoothByAveraging(f_foot_stretch_);
	//f_balance_back_forth_smooth_ = post_processing_.SmoothByAveraging(f_balance_back_forth_);
	//f_balance_left_right_smooth_ = post_processing_.SmoothByAveraging(f_balance_left_right_);
	//f_velocity_global_smooth_ = post_processing_.SmoothByAveraging(f_velocity_global_);
}

void FeatureExtractor::CheckBufferSize_(std::vector<float>& buffer, int size)
{
	if (buffer.size() > size)
		buffer.erase(buffer.begin());
}

float FeatureExtractor::GetJointDisplacement_(Sample& sample_latest, Sample& sample_second, nite::JointType joint)
{
	Point3f point_latest = sample_latest.GetJointPosition(joint);
	Point3f point_second = sample_second.GetJointPosition(joint);
	return geometry_.EuclideanDistance(point_latest, point_second);
}

//	Shift the whole skeleton based on a reference point 
float FeatureExtractor::GetJointDisplacement_Shifted_(Sample& sample_latest, Sample& sample_second, JointType joint, JointType ref_joint)
{
	//
	// Displacement of reference point
	//
	Point3f ref_latest = sample_latest.GetJointPosition(ref_joint);
	Point3f ref_second = sample_second.GetJointPosition(ref_joint);
	Point3f ref_disp = Point3f(ref_second.x - ref_latest.x, ref_second.y - ref_latest.y, ref_second.z - ref_latest.z);
	//
	//	Shift the second point
	//
	Point3f point_latest = sample_latest.GetJointPosition(joint);
	Point3f point_second = sample_second.GetJointPosition(joint);
	point_second.x -= ref_disp.x;
	point_second.y -= ref_disp.y;
	point_second.z -= ref_disp.z;
	return geometry_.EuclideanDistance(point_latest, point_second);
}

void FeatureExtractor::GetF_HandVelocity_(Sample& sample_latest, Sample& sample_second)
{
	float velocity_left_hand = GetJointDisplacement_Shifted_(sample_latest, sample_second, JOINT_LEFT_HAND, JOINT_LEFT_SHOULDER);
	float velocity_right_hand = GetJointDisplacement_Shifted_(sample_latest, sample_second, JOINT_RIGHT_HAND, JOINT_RIGHT_SHOULDER);
	f_velocity_left_hand_.push_back(velocity_left_hand);
	f_velocity_right_hand_.push_back(velocity_right_hand);
	CheckBufferSize_(f_velocity_left_hand_, FEATURE_BUFF_SZ_VELOCITY_LEFT_HAND);
	CheckBufferSize_(f_velocity_right_hand_, FEATURE_BUFF_SZ_VELOCITY_RIGHT_HAND);
}

void FeatureExtractor::GetF_GlobalVelocity_(Sample& sample_latest, Sample& sample_second)
{
	std::vector<nite::JointType> centroid_joints;
	centroid_joints.push_back(nite::JOINT_HEAD);
	centroid_joints.push_back(nite::JOINT_NECK);
	centroid_joints.push_back(nite::JOINT_LEFT_HAND);
	centroid_joints.push_back(nite::JOINT_RIGHT_HAND);
	centroid_joints.push_back(nite::JOINT_TORSO);
	centroid_joints.push_back(nite::JOINT_LEFT_FOOT);
	centroid_joints.push_back(nite::JOINT_RIGHT_FOOT);
	nite::Point3f centroid_latest = geometry_.CentroidOfJoints(sample_latest.GetSkeleton(), centroid_joints);
	nite::Point3f centroid_second = geometry_.CentroidOfJoints(sample_second.GetSkeleton(), centroid_joints);
	float velocity_global = geometry_.EuclideanDistance(centroid_latest, centroid_second);
	f_velocity_global_.push_back(velocity_global);
	CheckBufferSize_(f_velocity_global_, FEATURE_BUFF_SZ_VELOCITY_GLOBAL);
}

void FeatureExtractor::GetF_FeetVelocity_(Sample& sample_latest, Sample& sample_second)
{
	std::vector<nite::JointType> feet_joints;
	feet_joints.push_back(nite::JOINT_LEFT_FOOT);
	feet_joints.push_back(nite::JOINT_RIGHT_FOOT);
	nite::Point3f pos_feet_1 = geometry_.CentroidOfJoints(sample_latest.GetSkeleton(), feet_joints);
	nite::Point3f pos_feet_2 = geometry_.CentroidOfJoints(sample_second.GetSkeleton(), feet_joints);
	float displacement_foot = geometry_.EuclideanDistance(pos_feet_1, pos_feet_2);
	f_velocity_foot_.push_back(displacement_foot);
	CheckBufferSize_(f_velocity_foot_, FEATURE_BUFF_SZ_VELOCITY_FOOT);
}

void FeatureExtractor::GetF_Energy_(Sample& sample_latest, Sample& sample_second)
{
	// 1- Compute velocity of joints
	//
	float velocity_head = GetJointDisplacement_(sample_latest, sample_second, JOINT_HEAD);
	float velocity_neck = GetJointDisplacement_(sample_latest, sample_second, JOINT_NECK);
	float velocity_left_elbow = GetJointDisplacement_(sample_latest, sample_second, JOINT_LEFT_ELBOW);
	float velocity_right_elbow = GetJointDisplacement_(sample_latest, sample_second, JOINT_RIGHT_ELBOW);
	float velocity_torso = GetJointDisplacement_(sample_latest, sample_second, JOINT_TORSO);
	float velocity_left_shoulder = GetJointDisplacement_(sample_latest, sample_second, JOINT_LEFT_SHOULDER);
	float velocity_right_shoulder = GetJointDisplacement_(sample_latest, sample_second, JOINT_RIGHT_SHOULDER);
	float velocity_left_hand = GetJointDisplacement_(sample_latest, sample_second, JOINT_LEFT_HAND);
	float velocity_right_hand = GetJointDisplacement_(sample_latest, sample_second, JOINT_RIGHT_HAND);
	float velocity_left_hip = GetJointDisplacement_(sample_latest, sample_second, JOINT_LEFT_HIP);
	float velocity_right_hip = GetJointDisplacement_(sample_latest, sample_second, JOINT_RIGHT_HIP);
	float velocity_left_knee = GetJointDisplacement_(sample_latest, sample_second, JOINT_LEFT_KNEE);
	float velocity_right_knee = GetJointDisplacement_(sample_latest, sample_second, JOINT_RIGHT_KNEE);
	float velocity_left_foot = GetJointDisplacement_(sample_latest, sample_second, JOINT_LEFT_FOOT);
	float velocity_right_foot = GetJointDisplacement_(sample_latest, sample_second, JOINT_RIGHT_FOOT);
	//
	// 2 - Velocity of combined joints
	//
	std::vector<nite::JointType> head_neck_joints;
	head_neck_joints.push_back(nite::JOINT_HEAD);
	head_neck_joints.push_back(nite::JOINT_NECK);
	nite::Point3f pos_head_neck_1 = geometry_.CentroidOfJoints(sample_latest.GetSkeleton(), head_neck_joints);
	nite::Point3f pos_head_neck_2 = geometry_.CentroidOfJoints(sample_second.GetSkeleton(), head_neck_joints);
	float velocity_head_neck = geometry_.EuclideanDistance(pos_head_neck_1, pos_head_neck_2);

	std::vector<nite::JointType> torso_joints;
	torso_joints.push_back(nite::JOINT_TORSO);
	torso_joints.push_back(nite::JOINT_LEFT_SHOULDER);
	torso_joints.push_back(nite::JOINT_RIGHT_SHOULDER);
	nite::Point3f pos_torso_shoulders_1 = geometry_.CentroidOfJoints(sample_latest.GetSkeleton(), torso_joints);
	nite::Point3f pos_torso_shoulders_2 = geometry_.CentroidOfJoints(sample_second.GetSkeleton(), torso_joints);
	float velocity_torso_shoulders = geometry_.EuclideanDistance(pos_torso_shoulders_1, pos_torso_shoulders_2);

	std::vector<nite::JointType> hip_joints;
	hip_joints.push_back(nite::JOINT_LEFT_HIP);
	hip_joints.push_back(nite::JOINT_RIGHT_HIP);
	nite::Point3f pos_hip_1 = geometry_.CentroidOfJoints(sample_latest.GetSkeleton(), hip_joints);
	nite::Point3f pos_hip_2 = geometry_.CentroidOfJoints(sample_second.GetSkeleton(), hip_joints);
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

void FeatureExtractor::GetF_Direction_BackForth_(Sample& sample_latest, Sample& sample_second)
{
	// Compute amount of back-forth movement between 2 most recent frames
	// The accurate amount of back-forth displacement will be computed later on in the smoothing step
	//
	// Compute distance on the Oy axis
	//
	nite::Point3f p1 = sample_latest.GetJointPosition(JOINT_TORSO);
	nite::Point3f p2 = sample_second.GetJointPosition(JOINT_TORSO);
	float distance = p2.z - p1.z;
	f_direction_back_forth_.push_back(distance);
	CheckBufferSize_(f_direction_back_forth_, FEATURE_BUFF_SZ_DIRECTION);
}

void FeatureExtractor::GetF_FeetStretch_(Sample& sample_latest)
{
	float distance_shoulders = geometry_.EuclideanDistance(
		sample_latest.GetJointPosition(nite::JOINT_LEFT_SHOULDER),
		sample_latest.GetJointPosition(nite::JOINT_RIGHT_SHOULDER));
	float distance_foot = geometry_.EuclideanDistance(
		sample_latest.GetJointPosition(nite::JOINT_LEFT_FOOT),
		sample_latest.GetJointPosition(nite::JOINT_RIGHT_FOOT));
	float foot_stretch = distance_foot / distance_shoulders;
	f_foot_stretch_.push_back(foot_stretch);
	CheckBufferSize_(f_foot_stretch_, FEATURE_BUFF_SZ_FOOT_STRETCH);
}

void FeatureExtractor::GetF_BalanceBackForth_(Sample& sample_latest)
{
	std::vector<nite::JointType> foot_joints;
	foot_joints.push_back(nite::JOINT_LEFT_FOOT);
	foot_joints.push_back(nite::JOINT_RIGHT_FOOT);
	nite::Point3f foot_center = geometry_.CentroidOfJoints(sample_latest.GetSkeleton(), foot_joints);

	std::vector<nite::JointType> shoulder_joints;
	shoulder_joints.push_back(nite::JOINT_LEFT_SHOULDER);
	shoulder_joints.push_back(nite::JOINT_RIGHT_SHOULDER);
	nite::Point3f shoulders_center = geometry_.CentroidOfJoints(sample_latest.GetSkeleton(), shoulder_joints);

	// Project to the ground plane
	foot_center.y = 0;
	shoulders_center.y = 0;
	float leaning_back_forth = geometry_.EuclideanDistance(foot_center, shoulders_center);

	// The sign depend on which side Shoulders_Center compare to the line created by Foot positions
	nite::Point3f foot_left = sample_latest.GetJointPosition(JOINT_LEFT_FOOT);
	nite::Point3f foot_right = sample_latest.GetJointPosition(JOINT_RIGHT_FOOT);
	
	float sign = geometry_.Position_Point_Line(foot_left.x, foot_left.z, foot_right.x, foot_right.z, shoulders_center.x, shoulders_center.z);
	leaning_back_forth *= sign;
	f_balance_back_forth_.push_back(leaning_back_forth);
	CheckBufferSize_(f_balance_back_forth_, FEATURE_BUFF_SZ_BALANCE_BACK_FORTH);
}

void FeatureExtractor::GetF_BalanceLeftRight_(Sample& sample_latest)
{
	nite::Point3f foot_left_2d = sample_latest.GetJointPosition(nite::JOINT_LEFT_FOOT);
	foot_left_2d.y = 0;
	nite::Point3f foot_right_2d = sample_latest.GetJointPosition(nite::JOINT_RIGHT_FOOT);
	foot_right_2d.y = 0;
	nite::Point3f torso_2d = sample_latest.GetJointPosition(nite::JOINT_TORSO);
	torso_2d.y = 0;

	float distance_left = geometry_.EuclideanDistance(torso_2d, foot_left_2d);
	float distance_right = geometry_.EuclideanDistance(torso_2d, foot_right_2d);
	float leaning_left_right = distance_left - distance_right;

	f_balance_left_right_.push_back(leaning_left_right);
	CheckBufferSize_(f_balance_left_right_, FEATURE_BUFF_SZ_BALANCE_LEFT_RIGHT);
}

int FeatureExtractor::GetActualBufferSize()
{
	return f_balance_left_right_.size();
}

#pragma endregion



