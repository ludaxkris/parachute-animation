////////////////////////////////////////
// particleSystem.cpp
////////////////////////////////////////


#include "particleSystem.h"

void ParticleSystem::Update(float deltaTime, int anchorLength, int anchorType) {
	// Compute forces
	Vector3 gravity(0,-9.8,0);

	//Two outer anchors
	if( anchorType == 0 ) {
		for(int i=0; i<NumParticles; ++i) {
			if(i==0 || i==anchorLength-1)
				continue;
			Vector3 force = gravity * particles.at(i)->Mass; // f=mg
			particles.at(i)->ApplyForce(force);
		}

		// Integrate
		for(int i=0; i<NumParticles; ++i) {
			if(i==0 || i==anchorLength-1)
				continue;
			particles.at(i)->Update(deltaTime);
		}
	}
	//Anchor top edge
	else if( anchorType == 1 ) {
		for(int i=anchorLength; i<NumParticles; ++i) {			
			Vector3 force = gravity * particles.at(i)->Mass; // f=mg
			particles.at(i)->ApplyForce(force);
		}

		// Integrate
		for(int i=anchorLength; i<NumParticles; ++i) {			
			particles.at(i)->Update(deltaTime);
		}
	}
	//No anchor
	else if( anchorType == 2 ) {
		for(int i=0; i<NumParticles; ++i) {			
			Vector3 force = gravity * particles.at(i)->Mass; // f=mg
			particles.at(i)->ApplyForce(force);
		}

		// Integrate
		for(int i=0; i<NumParticles; ++i) {			
			particles.at(i)->Update(deltaTime);
		}
	}
}

void ParticleSystem::Draw() {
	for(int i=0; i<particles.size(); ++i) {
		particles.at(i)->Draw();
	}
}