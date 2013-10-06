////////////////////////////////////////
// channel.h
////////////////////////////////////////

#ifndef CSE169_CHANNEL_H
#define CSE169_CHANNEL_H

#include "token.h"
#include "keyframe.h"
#include <vector>


class Channel {
public:

	void Load(Tokenizer &t);
	void precompute();
	float evaluate(float t);
	
	int getExtraIn();
	int getExtraOut();

	char extraIn[20];
	char extraOut[20];
	std::vector <Keyframe*> keys;
	int numKeys;
	Keyframe * firstKey, * lastKey;
	//stores an array of keyframes
	//extrapolation
	//constant, linear, cyclic, cyclic offset, bounce

};



#endif