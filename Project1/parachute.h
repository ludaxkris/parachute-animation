////////////////////////////////////////
// parachute.h
////////////////////////////////////////

#ifndef CSE169_PARACHUTE_H
#define CSE169_PARACHUTE_H

#include "matrix34.h"
#include "vector3.h"
#include "triangle.h"
#include "vertex.h"
#include "cloth.h"
#include "particleSystem.h"
#include "particle.h"
#include <vector>


class Parachute {
public:
	Parachute();
	void MakeParachute();
	void MakeRope(int length, int clothSize);
	void MakeCube(float size);

	void DrawLines(Vertex * vert0, Vertex * vert1);

	/////Cloth Properties
	void MakeCloth(int width, int height, Vector3 initPosition, float triangleSize, int plane);
	void Draw(int drawStyle);
	void Update(float windFactor, float ground);


	//Forces
	void ComputeAerodynamics(Vector3 air);
	void CollisionGround(float ground, float elasticity, float friction);

	ParticleSystem psystem;
	std::vector <Triangle*> triangles;
	std::vector <Vertex*> vertices;
	std::vector <SpringDamper*> springs;

	int clothHeight, clothWidth;

	//Joint parts
	Particle *topRope1, *topRope2, *topRope3, *topRope4;	
	Particle *topCube1, *topCube2, *topCube3, *topCube4;

};

#endif