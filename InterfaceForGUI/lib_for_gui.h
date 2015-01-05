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