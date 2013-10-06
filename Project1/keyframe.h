////////////////////////////////////////
// keyframe.h
////////////////////////////////////////

#ifndef CSE169_KEYFRAME_H
#define CSE169_KEYFRAME_H

#include "core.h"
#include "token.h"

class Keyframe {
public:
	void Load(Tokenizer &t);
	void cubicCoef(float p0, float p1, float v0, float v1);
	float evalCubic(float time);

	int getRuleIn();
	int getRuleOut();

	float time;
	float value;					//current position
	float tangentIn, tangentOut;	//tangent values


	char ruleIn[10], ruleOut[10];	//Tangent rules
	float a, b, c, d;				//cubic coefficents
	float timeDiff;
	

	//data structures
	//linked list, doubly linked list, array

	//tangent rules
	//flat, linear, smmoth, fixed

};



#endif