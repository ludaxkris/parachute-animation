////////////////////////////////////////
// particle.h
////////////////////////////////////////

#ifndef CSE169_PARTICLE_H
#define CSE169_PARTICLE_H

#include "core.h"
#include "vector3.h"


class Particle {
public:
	Particle(float x, float y, float z);
	Particle() {Particle(0, 0, 0);};

	float Mass;			// Constant
	Vector3 Position;	// Evolves frame to frame
	Vector3 Velocity;	// Evolves frame to frame
	Vector3 Force;		// Reset and re-computed each frame

	void Update(float deltaTime);
	void Draw();
	void ApplyForce(Vector3 &f);

	
};



#endif