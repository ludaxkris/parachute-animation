////////////////////////////////////////
// particleSystem.h
////////////////////////////////////////

#ifndef CSE169_PARTICLESYSTEM_H
#define CSE169_PARTICLESYSTEM_H

#include "core.h"
#include "particle.h"
#include <vector>

class ParticleSystem {
public:
	int NumParticles;
	std::vector<Particle *> particles;		//Particle array

	void Update(float deltaTime, int anchorLength, int anchorType);
	void Draw();
};



#endif