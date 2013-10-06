////////////////////////////////////////
// springDamper.h
////////////////////////////////////////

#ifndef CSE169_SPRINGDAMPER_H
#define CSE169_SPRINGDAMPER_H

#include "core.h"
#include "particle.h"


class SpringDamper {
public:
	SpringDamper(float kspring, float kdamp, float restlength);
	float SpringConstant,DampingFactor;
	float RestLength;
	Particle *P1,*P2;

	void Draw();

	void ComputeForce();
};



#endif