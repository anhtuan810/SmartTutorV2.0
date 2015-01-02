//
//  Smart Tutor v1.0
//	InterfaceForGUI
//
//  Created: 2014.08.14
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//
extern "C" { __declspec(dllexport) bool ITurnOnKinectSensor(); }
//extern "C" { __declspec(dllexport) bool IStartRecordingONI(char* file_name); }
//extern "C" { __declspec(dllexport) void IStopRecordingONI(); }
//extern "C" { __declspec(dllexport) void ITurnOffKinectSensor(); }
extern "C" { __declspec(dllexport) void IQuerrySensor(); }
extern "C" { __declspec(dllexport) char* IGrabFrame(); }
//
//
//extern "C" { __declspec(dllexport) bool IGenerateFeaturesFromONI(char* ONI_file_name, char* data_folder); }
//extern "C" { __declspec(dllexport) void IPerformFeatureAnalysis(char* data_folder); }
//extern "C" { __declspec(dllexport) void ISaveAnalysisResult(char* result_folder); }