////////////////////////////////////////
// dof.h
////////////////////////////////////////

#ifndef CSE169_DOF_H
#define CSE169_DOF_H

#include <math.h>

#define PI 3.14159

class Dof {
public:
	Dof() {minDof=-100000; maxDof=100000; value=0.0; morphValue=1.0;}
	void setMinMax(float min, float max);
	float getMax();
	float getMin();
	
	void setValue(float val);
	float getValue();
	void increaseValue(float val);
	
	float getMorphValue();
	void increaseMorph(float val);

private:
	float minDof;
	float maxDof;
	float value;

	float morphValue;
};


#endif
