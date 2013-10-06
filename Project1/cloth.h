////////////////////////////////////////
// cloth.h
////////////////////////////////////////

#ifndef CSE169_CLOTH_H
#define CSE169_CLOTH_H

#include "core.h"
#include "vector3.h"
#include "matrix34.h"
#include "vertex.h"
#include "triangle.h"
#include "springDamper.h"
#include "particleSystem.h"
#include <vector>


class Cloth {
public:
	Cloth();
	
	void createCloth(int width, int height, Vector3 initPosition, float triangleSize, int plane);
	void Draw(int drawStyle);
	void Update(float windFactor, float ground);

	//Cloth motion
	void translateCloth(Vector3 translation);
	void rotateCloth(Matrix34 rotMtx);

	//Forces
	void ComputeAerodynamics(Vector3 air);
	void CollisionGround(float ground, float elasticity, float friction);

	ParticleSystem psystem;
	std::vector <Triangle*> triangles;
	std::vector <Vertex*> vertices;
	std::vector <SpringDamper*> springs;

	int clothHeight, clothWidth;
};

#endif