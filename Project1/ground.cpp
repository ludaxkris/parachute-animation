////////////////////////////////////////
// ground.cpp
////////////////////////////////////////


#include "core.h"
#include "ground.h"
#include "matrix34.h"


Ground::Ground() {
}


void Ground::MakeGround(float size, float positionY) {
	//Square ground
	float halfSize = size/2;
	vert0 = new Vertex(-halfSize, positionY, -halfSize);
	vert1 = new Vertex(halfSize, positionY, -halfSize);
	vert2 = new Vertex(-halfSize, positionY, halfSize);
	vert3 = new Vertex(halfSize, positionY, halfSize);

	tri1 = new Triangle(vert0, vert1, vert3);
	tri2 = new Triangle(vert0, vert3, vert2);
}

float Ground::getPositionY() {
	return vert0->weightPos.y;
}

void Ground::setPositionY(float gnd) {
	vert0->weightPos.y = gnd;
	vert1->weightPos.y = gnd;
	vert2->weightPos.y = gnd;
	vert3->weightPos.y = gnd;
}

void Ground::Update() {

}

void Ground::Draw(int drawType) {
	if(drawType == 0) {	//draw solid
		tri1->Draw(Matrix34::IDENTITY);
		tri2->Draw(Matrix34::IDENTITY);
	}
	else if( drawType == 1 ) {	//draw wire
		DrawLines(vert0, vert1);
		DrawLines(vert1, vert2);
		DrawLines(vert2, vert3);
		DrawLines(vert0, vert3);
		DrawLines(vert1, vert3);
		DrawLines(vert0, vert2);
	}
}

void Ground::DrawLines(Vertex * vert0, Vertex * vert1) {
	float ind1[3] = {vert0->weightPos.x, vert0->weightPos.y, vert0->weightPos.z};
	float ind2[3] = {vert1->weightPos.x, vert1->weightPos.y, vert1->weightPos.z};

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(Matrix34::IDENTITY);
	glShadeModel(GL_SMOOTH);

	glBegin(GL_LINES);
		glVertex3fv(ind1);
		glVertex3fv(ind2);
	glEnd();
}