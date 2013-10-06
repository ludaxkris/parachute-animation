////////////////////////////////////////
// player.cpp
////////////////////////////////////////


#include "core.h"
#include "player.h"

void Player::setClip(Animation &clip) {
	anim = &clip;
}

const Pose & Player::getPose() {
	return p;
}

void Player::Update() {
	//Update time
	//evaluate animation
	//output pose
	p.cleanPose();
	anim->Evaluate(time, p);
	
	clock_t clk = clock() - baseClk;
	//time = (float) clk / CLOCKS_PER_SEC;

	time += speed;

	//Check if time is out of range
	if(time > timeEnd) {
		time = timeBeg;
	}
}

void Player::setTime(float beg, float end) {
	timeBeg = beg;
	timeEnd = end;
}

void Player::setSpeed(float s) {
	speed = s;
}

void Player::increaseSpeed(float s) {
	speed += s;
}