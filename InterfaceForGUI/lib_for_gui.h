extern "C" { __declspec(dllexport) bool ITurnOnKinectSensor(); }
extern "C" { __declspec(dllexport) bool ITurnOnONIFile(char* file_name); }
extern "C" { __declspec(dllexport) void IQuerySensor(); }
extern "C" { __declspec(dllexport) char* IGrabCurrentColorFrame(); }