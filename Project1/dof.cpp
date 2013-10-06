////////////////////////////////////////
// dof.cpp
////////////////////////////////////////


#include "dof.h"


void Dof::setMinMax(float min, float max) {
	maxDof = max;
	minDof = min;
}

float Dof::getMax() {
	return maxDof;
}

float Dof::getMin() {
	return minDof;
}

void Dof::setValue(float val) {
	value = val;
}

float Dof::getValue() {
	if( value > maxDof )
		return maxDof;
	if( value < minDof )
		return minDof;
	return value;
}

void Dof::increaseValue(float val) {
	value += val;
}

float Dof::getMorphValue() {
	if( morphValue > 1.0 ) {
		morphValue = 1.0;
	}
	if( morphValue < 0.0 ) {
		morphValue = 0.0;
	}
	return morphValue;
}

void Dof::increaseMorph(float val) {
	morphValue += val;
}