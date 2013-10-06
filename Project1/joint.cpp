////////////////////////////////////////
// joint.cpp
////////////////////////////////////////


#include "core.h"
#include "joint.h"
#include "matrix34.h"
#include "vector3.h"
#include "dof.h"


Joint::Joint() {
	LocalMtx = Matrix34::IDENTITY;
	WorldMtx = Matrix34::IDENTITY;
	position = Vector3::ORIGIN;
	boxmax = Vector3(0.1,0.1,0.1);
	boxmin = Vector3(-0.1,-0.1,-0.1);

	//Set children to NULL;
	firstChild = NULL;
	sib = NULL;
}

bool Joint::Load(Tokenizer &token, std::vector<Joint*> & jointArray) {	
	token.FindToken("{");
	while(1) {
		char temp[256];
		token.GetToken(temp);

		if(strcmp(temp,"offset") == 0) {
			position.x = token.GetFloat();
			position.y = token.GetFloat();
			position.z = token.GetFloat();
			//L = L.Dot(L.MakeTranslate(offsetx, offsety, offsetz), L);
		}
		else if(strcmp(temp,"boxmin") == 0) {
			boxmin.x = token.GetFloat();
			boxmin.y = token.GetFloat();
			boxmin.z = token.GetFloat();
		}
		else if(strcmp(temp,"boxmax") == 0) {
			boxmax.x = token.GetFloat();
			boxmax.y = token.GetFloat();
			boxmax.z = token.GetFloat();
		}
		else if(strcmp(temp,"rotxlimit") == 0) {
			float x = token.GetFloat();
			float y = token.GetFloat();
			dofx.setMinMax(x, y);
		}
		else if(strcmp(temp,"rotylimit") == 0) {
			float x = token.GetFloat();
			float y = token.GetFloat();
			dofy.setMinMax(x, y);
		}
		else if(strcmp(temp,"rotzlimit") == 0) {
			float x = token.GetFloat();
			float y = token.GetFloat();
			dofz.setMinMax(x, y);
		}
		else if(strcmp(temp,"pose") == 0) {
			dofx.setValue(token.GetFloat());
			dofy.setValue(token.GetFloat());
			dofz.setValue(token.GetFloat());
		}		
		else if(strcmp(temp,"balljoint") == 0) {
			Joint *jnt = new Joint();
			jointArray.push_back(jnt);
			jnt->Load(token, jointArray);
			addChild(*jnt);
		}
		else if(strcmp(temp,"}") ==0 ) {
			Matrix34 rotx;
			Matrix34 roty;
			Matrix34 rotz;
			rotx.MakeRotateX(dofx.getValue());
			roty.MakeRotateY(dofy.getValue());
			rotz.MakeRotateZ(dofz.getValue());

			//LocalMtx.Dot(rotx, LocalMtx);
			//LocalMtx.Dot(roty, LocalMtx);
			//LocalMtx.Dot(rotz, LocalMtx);

			LocalMtx.Dot(LocalMtx, rotz);
			LocalMtx.Dot(LocalMtx, roty);
			LocalMtx.Dot(LocalMtx, rotx);

			return true;
		}
		else token.SkipLine(); // Unrecognized token
	}
}

void Joint::addChild(Joint &jnt) {
	if( firstChild == NULL ) //check if there are any first children
		firstChild = &jnt;
	else //if there are FC, then add as a sibling of FC
		firstChild->addSib(jnt);
}

void Joint::addSib(Joint &jnt) {
	if( sib == NULL )
		sib = &jnt;
	else
		sib->addSib(jnt);
}

void Joint::Update(Matrix34 &parent) {
	//could make a 3dof rotate matrix
	// Compute LocalMatrix
	LocalMtx = Matrix34::IDENTITY;
	Matrix34 rotx;
	Matrix34 roty;
	Matrix34 rotz;
	rotx.MakeRotateX(dofx.getValue());
	roty.MakeRotateY(dofy.getValue());
	rotz.MakeRotateZ(dofz.getValue());

	LocalMtx.Dot(LocalMtx, rotz);
	LocalMtx.Dot(LocalMtx, roty);
	LocalMtx.Dot(LocalMtx, rotx);
	
	LocalMtx.d = position;

	// Compute WorldMatrix
	WorldMtx.Dot(parent, LocalMtx);

	parentMtx = parent;

	// Recursively call Update() on children
	if(firstChild != NULL)
		firstChild->Update(WorldMtx);
	if(sib != NULL)
		sib->Update(parent);
}


void Joint::Draw() {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(WorldMtx);
	drawWireBox(boxmin.x, boxmin.y, boxmin.z, boxmax.x, boxmax.y, boxmax.z);

	if(firstChild != NULL)
		firstChild->Draw();
	if(sib != NULL)
		sib->Draw();
	// Do some OpenGL
	// Recursively call Draw() on children
}


Matrix34 Joint::GetWorldMatrix() {	
	return WorldMtx;
}

void Joint::generateArray(std::vector<Joint*> & jointArray) {
	if(firstChild != NULL) {
		jointArray.push_back(firstChild);
		firstChild->generateArray(jointArray);
	}
	if(sib != NULL) {
		jointArray.push_back(sib);
		sib->generateArray(jointArray);
	}
}

void Joint::updatePose(const Pose &p, int startPos) {
	dofx.setValue(p.positions.at(startPos));
	dofy.setValue(p.positions.at(startPos+1));
	dofz.setValue(p.positions.at(startPos+2));
}

void Joint::updateRoot(const Pose &p) {
	position.x = p.positions.at(0);
	position.y = p.positions.at(1);
	position.z = p.positions.at(2);
}