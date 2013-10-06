////////////////////////////////////////
// skel.cpp
////////////////////////////////////////


#include "skel.h"
#include "token.h"
#include "Matrix34.h"


bool Skel::Load(const char *file) {
	Tokenizer token;
	token.Open(file);
	token.FindToken("balljoint");
	// Parse tree
	root = new Joint;
	jointArray.push_back(root);
	root->Load(token, jointArray);

	//jointArray.push_back(root);
	//root->generateArray(jointArray);
	// Finish
	token.Close();
	return true;
}

void Skel::Update() {
	root->Update(Matrix34::IDENTITY);
}

void Skel::Draw() {
	root->Draw();
}

Matrix34 Skel::GetWorldMatrix(int jointNum) {
	return jointArray.at(jointNum)->GetWorldMatrix();;
}

int Skel::numberJoints() {
	return jointArray.size();
}

Joint * Skel::getJoint(int jointNum) {
	return jointArray.at(jointNum);
}

void Skel::updatePose(Pose p) {
	root->updateRoot(p);

 	for(int i=0; i<jointArray.size(); ++i) {
		jointArray.at(i)->updatePose(p, (i+1)*3);
	}
}