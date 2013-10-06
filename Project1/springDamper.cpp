////////////////////////////////////////
// springDamper.cpp
////////////////////////////////////////

#include "springDamper.h"
#include "Matrix34.h"


SpringDamper::SpringDamper(float kspring, float kdamp, float restlength) {
	SpringConstant = kspring;
	DampingFactor = kdamp;
	RestLength = restlength;
}


void SpringDamper::Draw() {
	float ind1[3] = {P1->Position.x, P1->Position.y, P1->Position.z};
	float ind2[3] = {P2->Position.x, P2->Position.y, P2->Position.z};

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(Matrix34::IDENTITY);
	glShadeModel(GL_SMOOTH);

	glBegin(GL_LINES);
		glVertex3fv(ind1);
		glVertex3fv(ind2);
	glEnd();
}

void SpringDamper::ComputeForce() {
	//spring damper
	//f = -ks * (l0-|l|)*e - kd * (v1-v2);

	Vector3 force;

	//spring
	Vector3 xDiff = P2->Position - P1->Position;
	float spring = - SpringConstant * (RestLength - xDiff.Mag());

	//damp
	float vDiff = xDiff.Normalize().Dot(P1->Velocity) - xDiff.Normalize().Dot(P2->Velocity);
	float damp = -DampingFactor * vDiff;

	force = (spring + damp) * xDiff.Normalize();

	P1->ApplyForce(force);
	P2->ApplyForce(-force);	
}