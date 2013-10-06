////////////////////////////////////////
// triangle.h
////////////////////////////////////////

#ifndef CSE169_TRIANGLE_H
#define CSE169_TRIANGLE_H

#include "token.h"
#include "matrix34.h"
#include "vector3.h"
#include "vertex.h"
#include "dof.h"
#include "particle.h"


class Triangle {
public:
	Triangle();
	Triangle(Vertex * x, Vertex * y, Vertex * z);
	Triangle(Particle * x, Particle * y, Particle * z);
	Triangle(Vertex * x, Vertex * y, Vertex * z, Particle * xp, Particle * yp, Particle * zp);
	void Draw(Matrix34 worldMtx);
	void Update(Vector3 vair);

	void ComputeAerodynamics(float density, float drag, Vector3 vair);

	void Draw();

	
	Vector3 velocity;
	Vector3 normal;
	float area;

	Particle * part1;
	Particle * part2;
	Particle * part3;

	Vertex * index1;
	Vertex * index2;
	Vertex * index3;

};

#endif