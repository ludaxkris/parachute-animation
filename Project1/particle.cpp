////////////////////////////////////////
// particle.cpp
////////////////////////////////////////

#include "particle.h"
#include "Matrix34.h"


Particle::Particle(float x, float y, float z) {
	Position = Vector3(x, y, z);
	Mass = 0.001;
	Force.Zero();
	Velocity.Zero();
}


void Particle::ApplyForce(Vector3 &f) {
	Force += f;	//add forces together
}

void Particle::Update(float deltaTime) {
	// Compute acceleration (Newton’s second law)
	Vector3 Accel = (1.0/Mass) * Force;

	// Compute new position & velocity
	Velocity += Accel * deltaTime;
	Position += Velocity * deltaTime;

	// Zero out Force vector
	Force.Zero();
}

void Particle::Draw() {
	float ind[3] = {Position.x, Position.y, Position.z};

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(Matrix34::IDENTITY);
	glShadeModel(GL_SMOOTH);

	glBegin(GL_POINTS);
		glVertex3fv(ind);
	glEnd();
}