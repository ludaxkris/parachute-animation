////////////////////////////////////////
// vector3.cpp
////////////////////////////////////////

#include "vector3.h"

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::XAXIS(1.0f,0.0f,0.0f);
Vector3 Vector3::YAXIS(0.0f,1.0f,0.0f);
Vector3 Vector3::ZAXIS(0.0f,0.0f,1.0f);
Vector3 Vector3::ORIGIN(0.0f,0.0f,0.0f);

////////////////////////////////////////////////////////////////////////////////

float * Vector3::convertToArray(float *floatArray) {
	floatArray[0] = x; 
	floatArray[1] = y; 
	floatArray[2] = z; 
	return floatArray;
}