//
//  Smart Tutor v2.0
//	Interface for GUI, create dynamic library to link from C++ to C#
//
//  Created: 2015.01.05
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

//
//	Controlling sensor
//
extern "C" { __declspec(dllexport) bool ITurnOnKinectSensor(); }
extern "C" { __declspec(dllexport) bool ITurnOnONIFile(char* file_name); }
extern "C" { __declspec(dllexport) void IQuerySensor(); }
extern "C" { __declspec(dllexport) void ITurnOff(); }
extern "C" { __declspec(dllexport) char* IGrabCurrentColorFrame(); }
//
//	Perform feature extraction
//
extern "C" { __declspec(dllexport) void IExtractFeatureNewFrame(); }
extern "C" { __declspec(dllexport) int IGetActualFeatureBufferSize(); }
//
//	Retrieve feature extraction result
//
extern "C" { __declspec(dllexport) float* IGetFeature_VelocityLeftHand(); }
extern "C" { __declspec(dllexport) float* IGetFeature_VelocityRightHand(); }
extern "C" { __declspec(dllexport) float* IGetFeature_VelocityFoot(); }
extern "C" { __declspec(dllexport) float* IGetFeature_VelocityGlobal(); }
extern "C" { __declspec(dllexport) float* IGetFeature_Energy(); }
extern "C" { __declspec(dllexport) float* IGetFeature_DirectionBackForth(); }
extern "C" { __declspec(dllexport) float* IGetFeature_FootStretch(); }
extern "C" { __declspec(dllexport) float* IGetFeature_BalanceBackForth(); }
extern "C" { __declspec(dllexport) float* IGetFeature_BalanceLeftRight(); }
//
//	Retrieve binary series
//
extern "C" { __declspec(dllexport) bool* IGetBinary_VelocityLeftHand_Low(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_VelocityLeftHand_High(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_VelocityRightHand_Low(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_VelocityRightHand_High(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_VelocityGlobal_Low(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_VelocityGlobal_High(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_VelocityFoot_Low(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_VelocityFoot_High(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_Energy_Low(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_Energy_High(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_Direction_Backward(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_Direction_Forward(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_Foot_Stretched(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_Foot_Closed(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_Balance_Backward(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_Balance_Forward(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_Balance_Left(); }
extern "C" { __declspec(dllexport) bool* IGetBinary_Balance_Right(); }

//
//	Perform overall assessment (scoring)
//
extern "C" { __declspec(dllexport) void IAssessOneFeatureSet(); }
extern "C" { __declspec(dllexport) int IGetActualScoreBufferSize(); }
//
//	Retrieve score as a series (aiming for live score and tracking score changes)
//
extern "C" { __declspec(dllexport) float* IGetScore_HandGesture(); }
extern "C" { __declspec(dllexport) float* IGetScore_GlobalMovement(); }
extern "C" { __declspec(dllexport) float* IGetScore_Energy(); }
extern "C" { __declspec(dllexport) float* IGetScore_Direction(); }
extern "C" { __declspec(dllexport) float* IGetScore_Posture(); }
extern "C" { __declspec(dllexport) float* IGetScore_Overall(); }