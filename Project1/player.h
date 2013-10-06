////////////////////////////////////////
// player.h
////////////////////////////////////////

#ifndef CSE169_PLAYER_H
#define CSE169_PLAYER_H


#include "core.h"
#include "animation.h"
#include "pose.h"
#include <time.h>

class Player {
public:
	Player() { timeBeg=0.0f; timeEnd=10.0f; time=0; speed=0.5; baseClk = clock();}
	void setClip(Animation &clip);
	const Pose &getPose();
	void Update();

	void setTime(float beg, float end);
	void setSpeed(float s);
	void increaseSpeed(float s);


	clock_t baseClk;
	float time;
	float speed;
	float timeBeg, timeEnd;
	Animation * anim;
	Pose p;
};



#endif