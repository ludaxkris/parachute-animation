////////////////////////////////////////
// keyframe.cpp
////////////////////////////////////////


#include "core.h"
#include "keyframe.h"

void Keyframe::Load(Tokenizer &token) {
	time = token.GetFloat();
	value = token.GetFloat();
	token.GetToken(ruleIn);
	token.GetToken(ruleOut);
}

int Keyframe::getRuleIn() {
	//flat = 0
	//linear = 1;
	//smooth = 2;
	//fixed = 3
	if(strcmp(ruleIn,"flat") == 0)
		return 0;
	else if(strcmp(ruleIn,"linear") == 0)
		return 1;
	else if(strcmp(ruleIn,"smooth") == 0)
		return 2;
	else 
		return 3;
}

int Keyframe::getRuleOut() {
	//flat = 0
	//linear = 1;
	//smooth = 2;
	//fixed = 3
	if(strcmp(ruleOut,"flat") == 0)
		return 0;
	else if(strcmp(ruleOut,"linear") == 0)
		return 1;
	else if(strcmp(ruleOut,"smooth") == 0)
		return 2;
	else 
		return 3;
}

void Keyframe::cubicCoef(float p0, float p1, float v0, float v1) {
	a = 2*p0 - 2*p1 + v0 + v1;
	b = -3*p0 + 3*p1 - 2*v0 - v1;
	c = v0;
	d = p0;
}

float Keyframe::evalCubic(float t) {
	float u = (t - time) * timeDiff;
	return d + u*(c + u*(b + u*a));
}