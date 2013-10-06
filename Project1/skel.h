////////////////////////////////////////
// skel.h
////////////////////////////////////////

#ifndef CSE169_SKEL_H
#define CSE169_SKEL_H

#include "joint.h"
#include "Matrix34.h"
#include "pose.h"
#include <vector>

class Skel {
public:
	bool Load(const char *file);
	void Update();
	void Draw();
	void updatePose(Pose p);

	Matrix34 GetWorldMatrix(int jointNum);
	int numberJoints();
	Joint * getJoint(int jointNum);

private:
	Joint * root;
	std::vector <Joint *> jointArray;
};


#endif
