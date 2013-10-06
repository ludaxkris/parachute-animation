////////////////////////////////////////
// joint.h
////////////////////////////////////////

#ifndef CSE169_JOINT_H
#define CSE169_JOINT_H

#include "token.h"
#include "matrix34.h"
#include "vector3.h"
#include "dof.h"
#include "pose.h"
#include <vector>


class Joint {
public:
	Joint();
	bool Load(Tokenizer &t, std::vector<Joint*> & jointArray);
	void addSib(Joint &jnt);
	void addChild(Joint &jnt);
	void Update(Matrix34 &parent);
	void Draw();

	void generateArray(std::vector<Joint*> & jointArray);
	void updatePose(const Pose & p, int startPos);
	void updateRoot(const Pose &p);

	Matrix34 GetWorldMatrix();

	Dof dofx;
	Dof dofy;
	Dof dofz;

private:
	//Box min/max positions
	Vector3 boxmin;
	Vector3 boxmax;
	//Vector3 pose;
	Vector3 position;
	Matrix34 LocalMtx;		//object space
	Matrix34 WorldMtx;		//world space

	Matrix34 parentMtx;



	//Tree pointers
	Joint * firstChild;
	Joint * sib;
};


#endif
