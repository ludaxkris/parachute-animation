////////////////////////////////////////
// ground.h
////////////////////////////////////////

#ifndef CSE169_GROUND_H
#define CSE169_GROUND_H

#include "matrix34.h"
#include "vector3.h"
#include "triangle.h"
#include "vertex.h"
#include <vector>


class Ground {
public:
	Ground();
	void MakeGround(float size, float positionY);
	void Update();
	void Draw(int drawType);
	void DrawLines(Vertex * vert0, Vertex * vert1);

	float getPositionY();
	void setPositionY(float gnd);


	Vertex * vert0;
	Vertex * vert1;
	Vertex * vert2;
	Vertex * vert3;
	Triangle * tri1;
	Triangle * tri2;

};

#endif