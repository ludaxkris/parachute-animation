////////////////////////////////////////
// animation.h
////////////////////////////////////////

#ifndef CSE169_ANIMATION_H
#define CSE169_ANIMATION_H

#include "core.h"
#include "pose.h"
#include "channel.h"
#include <vector>

class Animation {
public:
	void Load(const char *file);
	void Evaluate(float time,Pose &p);
	void Precompute();
	//stores an array of channels

	float rangeMin;
	float rangeMax;

	int numChannels;
	std::vector <Channel*> channels;
};



#endif