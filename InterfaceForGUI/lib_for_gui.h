//
//  Smart Tutor v2.0
//	Interface for GUI, create dynamic library to link from C++ to C#
//
//  Created: 2015.01.05
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

extern "C" { __declspec(dllexport) bool ITurnOnKinectSensor(); }
extern "C" { __declspec(dllexport) bool ITurnOnONIFile(char* file_name); }
extern "C" { __declspec(dllexport) void IQuerySensor(); }
extern "C" { __declspec(dllexport) void ITurnOff(); }
extern "C" { __declspec(dllexport) char* IGrabCurrentColorFrame(); }

extern "C" { __declspec(dllexport) void IExtractFeatureNewFrame(); }
extern "C" { __declspec(dllexport) int IGetActualFeatureBufferSize(); }

extern "C" { __declspec(dllexport) float* IGetFeature_VelocityLeftHand(); }
extern "C" { __declspec(dllexport) float* IGetFeature_VelocityRightHand(); }
extern "C" { __declspec(dllexport) float* IGetFeature_VelocityFoot(); }
extern "C" { __declspec(dllexport) float* IGetFeature_VelocityGlobal(); }
extern "C" { __declspec(dllexport) float* IGetFeature_Energy(); }
extern "C" { __declspec(dllexport) float* IGetFeature_FootStretch(); }
extern "C" { __declspec(dllexport) float* IGetFeature_BalanceBackForth(); }
extern "C" { __declspec(dllexport) float* IGetFeature_BalanceLeftRight(); }