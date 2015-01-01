#include "sample.h"

using namespace nite;

Sample::Sample()
{
	this->IsContainUser = false;
}

Sample::~Sample()
{

}

Sample::Sample(nite::Skeleton& skel)
{
	if (skel.getState() != SKELETON_TRACKED)
	{
		this->IsContainUser = false;
		return;
	}

	this->IsContainUser = true;

	head_ = Point3D(skel.getJoint(JOINT_HEAD).getPosition());
	left_shoulder_ = Point3D(skel.getJoint(JOINT_LEFT_SHOULDER).getPosition());
	right_shoulder_ = Point3D(skel.getJoint(JOINT_RIGHT_SHOULDER).getPosition());
	left_elbow_ = Point3D(skel.getJoint(JOINT_LEFT_ELBOW).getPosition());
	right_elbow_ = Point3D(skel.getJoint(JOINT_RIGHT_ELBOW).getPosition());
	left_hand_ = Point3D(skel.getJoint(JOINT_LEFT_HAND).getPosition());
	right_hand_ = Point3D(skel.getJoint(JOINT_RIGHT_HAND).getPosition());
	torso_ = Point3D(skel.getJoint(JOINT_TORSO).getPosition());
	left_hip_ = Point3D(skel.getJoint(JOINT_LEFT_HIP).getPosition());
	right_hip_ = Point3D(skel.getJoint(JOINT_RIGHT_HIP).getPosition());
	left_knee_ = Point3D(skel.getJoint(JOINT_LEFT_KNEE).getPosition());
	right_knee_ = Point3D(skel.getJoint(JOINT_RIGHT_KNEE).getPosition());
	left_foot_ = Point3D(skel.getJoint(JOINT_LEFT_FOOT).getPosition());
	right_foot_ = Point3D(skel.getJoint(JOINT_RIGHT_FOOT).getPosition());
}

Point3D Sample::GetHead()
{
	return head_;
}

Point3D Sample::GetNeck()
{
	return neck_;
}

Point3D Sample::GetLeft_Shoulder()
{
	return left_shoulder_;
}

Point3D Sample::GetRight_Shoulder()
{
	return right_shoulder_;
}

Point3D Sample::GetLeft_Elbow()
{
	return left_elbow_;
}

Point3D Sample::GetRight_Elbow()
{
	return right_elbow_;
}

Point3D Sample::GetLeft_Hand()
{
	return left_hand_;
}

Point3D Sample::GetRight_Hand()
{
	return right_hand_;
}

Point3D Sample::GetTorso()
{
	return torso_;
}

Point3D Sample::GetLeft_Hip()
{
	return left_hip_;
}

Point3D Sample::GetRight_Hip()
{
	return right_hip_;
}

Point3D Sample::GetLeft_Knee()
{
	return left_knee_;
}

Point3D Sample::GetRight_Knee()
{
	return right_knee_;
}

Point3D Sample::GetLeft_Foot()
{
	return left_foot_;
}

Point3D Sample::GetRight_Foot()
{
	return right_foot_;
}
