////////////////////////////////////////
// cloth.cpp
////////////////////////////////////////


#include "cloth.h"
#include <iostream>



Cloth::Cloth() {

}
//Procedural function to create a cloth
//given dimensions given by number of triangles. Each triangle will have
//a base of .1 size.
void Cloth::createCloth(int width, int height, Vector3 initPosition, float triangleSize, int plane) {

	////make sure width and height are even
	//if( width % 2 != 0 )
	//	width += 1;
	//if( height % 2 != 0 )
	//	height += 1;

	clothHeight = height;
	clothWidth = width;

	//Update particle system
	psystem.NumParticles = (width+1) * (height+1);
	float mass = 0.03;

	//decide which plane to draw cloth on.
	//xy = 0, xz = 1, yz = 2;

	//Create vertices, particles and set normals
	Vertex * vert;
	Particle * part;
	switch(plane) {
		case 0: //xy plane		
			for( int j=0; j<height+1; ++j ) {
				for( int i=0; i<width+1; ++i ) {
					part = new Particle(i*triangleSize + initPosition.x, -(j*triangleSize + initPosition.y), initPosition.z);
					vert = new Vertex(i*triangleSize + initPosition.x, -(j*triangleSize + initPosition.y), initPosition.z);					
					vert->setBaseNorm(0, 0, 1);
					part->Mass = mass;
					vertices.push_back(vert);
					psystem.particles.push_back(part);
				}
			}
			break;
		case 1: //xz plane
			for( int i=0; i<height+1; ++i ) {
				for( int j=0; j<width+1; ++j ) {
					part = new Particle(i*triangleSize + initPosition.x, initPosition.y, j*triangleSize + initPosition.z);
					vert = new Vertex(i*triangleSize + initPosition.x, initPosition.y, j*triangleSize + initPosition.z);
					vert->setBaseNorm(0, 1, 0);
					part->Mass = mass;
					vertices.push_back(vert);
					psystem.particles.push_back(part);
				}
			}			
			break;
		case 2: //yz plane
			for( int i=0; i<height+1; ++i ) {
				for( int j=0; j<width+1; ++j ) {
					part = new Particle(initPosition.x, i*triangleSize + initPosition.y, j*triangleSize + initPosition.z);
					vert = new Vertex(initPosition.x, i*triangleSize + initPosition.y, j*triangleSize + initPosition.z);
					vert->setBaseNorm(1, 0, 0);
					part->Mass = mass;
					vertices.push_back(vert);
					psystem.particles.push_back(part);
				}
			}
			break;
		default:
			//Error
			return;
	}

	//center cloth
	Vector3 translation = Vector3(-(width/2)*triangleSize, (height/2)*triangleSize, 0);
	for(int i=0; i<psystem.NumParticles; ++i) {
		psystem.particles.at(i)->Position += translation;
	}
	

	//loop through each square and assign index 
	int numPointsPerRow = (width+1);
	Triangle * tri;
	for( int j=0; j<height; ++j ) {
		for( int i=0; i<width; ++i ) {		

			//Top triangle
			Vertex * vert1 = vertices.at(i + (numPointsPerRow*j));
			Vertex * vert2 = vertices.at(i+1 + (numPointsPerRow*j));
			Vertex * vert3 = vertices.at(i+1 + (numPointsPerRow*(j+1)));

			Particle * part1 = psystem.particles.at(i + (numPointsPerRow*j));
			Particle * part2 = psystem.particles.at(i+1 + (numPointsPerRow*j));
			Particle * part3 = psystem.particles.at(i+1 + (numPointsPerRow*(j+1)));

			//tri = new Triangle(vert1, vert2, vert3);
			tri = new Triangle(vert1, vert2, vert3, part1, part2, part3);
			triangles.push_back(tri);

			//Bottom triangle
			Vertex * vert4 = vertices.at(i + (numPointsPerRow*j));			
			Vertex * vert5 = vertices.at(i+1 + (numPointsPerRow*(j+1)));
			Vertex * vert6 = vertices.at(i + (numPointsPerRow*(j+1)));

			Particle * part4 = psystem.particles.at(i + (numPointsPerRow*j));			
			Particle * part5 = psystem.particles.at(i+1 + (numPointsPerRow*(j+1)));
			Particle * part6 = psystem.particles.at(i + (numPointsPerRow*(j+1)));

			//tri = new Triangle(vert4, vert5, vert6);
			tri = new Triangle(vert4, vert5, vert6, part4, part5, part6);
			triangles.push_back(tri);
		}
	}

	//Assign particles to springdamper system
	SpringDamper * sdamper;
	float kspring = 15;
	float kdamp = .055;

	float kspring2 = 20;
	float kdamp2 = .05;

	//float kspring = 3;
	//float kdamp = .01;

	//float kspring2 = 3;
	//float kdamp2 = .01;


	float restLength = triangleSize; //0.3

	float crossRestlength = sqrtf( restLength * restLength * 2 );

	///////Apply single binding springs.
	for( int j=0; j<height; ++j ) {
		for( int i=0; i<width; ++i ) {	
			//cross links
			sdamper = new SpringDamper(kspring, kdamp, crossRestlength);			
			sdamper->P1 = psystem.particles.at(i + (numPointsPerRow*j));
			sdamper->P2 = psystem.particles.at(i+1 + (numPointsPerRow*(j+1)));
			springs.push_back(sdamper);

			sdamper = new SpringDamper(kspring, kdamp, crossRestlength);	
			sdamper->P1 = psystem.particles.at(i+1 + (numPointsPerRow*j));
			sdamper->P2 = psystem.particles.at(i + (numPointsPerRow*(j+1)));
			springs.push_back(sdamper);

			//Top link
			sdamper = new SpringDamper(kspring, kdamp, restLength);
			sdamper->P1 = psystem.particles.at(i + (numPointsPerRow*j));
			sdamper->P2 = psystem.particles.at(i+1 + (numPointsPerRow*j));
			springs.push_back(sdamper);

			//Left link
			sdamper = new SpringDamper(kspring, kdamp, restLength);
			sdamper->P1 = psystem.particles.at(i + (numPointsPerRow*j));
			sdamper->P2 = psystem.particles.at(i + (numPointsPerRow*(j+1)));
			springs.push_back(sdamper);
		}
	}

	//Outer right link
	for( int j=0; j<height; ++j ) {
		sdamper = new SpringDamper(kspring, kdamp, restLength);
		sdamper->P1 = psystem.particles.at(width + (numPointsPerRow*j));
		sdamper->P2 = psystem.particles.at(width + (numPointsPerRow*(j+1)));
		springs.push_back(sdamper);
	}

	//Outer bottom link
	for( int i=0; i<width; ++i ) {
		sdamper = new SpringDamper(kspring, kdamp, restLength);
		sdamper->P1 = psystem.particles.at(i + (numPointsPerRow*height));
		sdamper->P2 = psystem.particles.at(i+1 + (numPointsPerRow*height));
		springs.push_back(sdamper);
	}


	////////Apply double binding
	for( int j=0; j<height-1; ++j ) {
		for( int i=0; i<width-1; ++i ) {	
			//cross links
			sdamper = new SpringDamper(kspring2, kdamp2, crossRestlength*2);			
			sdamper->P1 = psystem.particles.at(i + (numPointsPerRow*j));
			sdamper->P2 = psystem.particles.at(i+2 + (numPointsPerRow*(j+2)));
			springs.push_back(sdamper);

			sdamper = new SpringDamper(kspring2, kdamp2, crossRestlength*2);	
			sdamper->P1 = psystem.particles.at(i+2 + (numPointsPerRow*j));
			sdamper->P2 = psystem.particles.at(i + (numPointsPerRow*(j+2)));
			springs.push_back(sdamper);

			//Top link
			sdamper = new SpringDamper(kspring2, kdamp2, restLength*2);
			sdamper->P1 = psystem.particles.at(i + (numPointsPerRow*j));
			sdamper->P2 = psystem.particles.at(i+2 + (numPointsPerRow*j));
			springs.push_back(sdamper);

			//Left link
			sdamper = new SpringDamper(kspring2, kdamp2, restLength*2);
			sdamper->P1 = psystem.particles.at(i + (numPointsPerRow*j));
			sdamper->P2 = psystem.particles.at(i + (numPointsPerRow*(j+2)));
			springs.push_back(sdamper);
		}
	}

	//Outer right link
	for( int j=0; j<height-1; ++j ) {
		sdamper = new SpringDamper(kspring2, kdamp2, restLength*2);
		sdamper->P1 = psystem.particles.at(width + (numPointsPerRow*j));
		sdamper->P2 = psystem.particles.at(width + (numPointsPerRow*(j+2)));
		springs.push_back(sdamper);
	}

	//Outer bottom link
	for( int i=0; i<width-1; ++i ) {
		sdamper = new SpringDamper(kspring2, kdamp2, restLength*2);
		sdamper->P1 = psystem.particles.at(i + (numPointsPerRow*height));
		sdamper->P2 = psystem.particles.at(i+2 + (numPointsPerRow*height));
		springs.push_back(sdamper);
	}
}

void Cloth::translateCloth(Vector3 translation) {
	//move anchor (top row)
	for(int i=0; i<clothWidth+1; ++i) {
		psystem.particles.at(i)->Position += translation;
	}
}

void Cloth::rotateCloth(Matrix34 rotMtx) {
	//move anchor (top row)
	Vector3 partPos;
	Matrix34 translate;
	float scale;
	for(int i=0; i<clothWidth+1; ++i) {
		partPos = psystem.particles.at(i)->Position;
		scale = partPos.Mag();

		translate.MakeTranslate(partPos.Normalize());
		translate.Dot(rotMtx, translate);

		partPos = translate.d * scale;
		psystem.particles.at(i)->Position = partPos;

	}
}

//Density of air: 1.2 kg/m3
//drag coefficient: 1.8 for paper
void Cloth::ComputeAerodynamics(Vector3 vair) {
	float density = 1.2;
	float drag = 1;
	
	for( int i=0; i<triangles.size(); ++i ) {
		triangles.at(i)->ComputeAerodynamics(density, drag, vair);
	}
}

void Cloth::CollisionGround(float ground, float elasticity, float friction) {
	for(int i=0; i<psystem.NumParticles; ++i) {
		Particle * p = psystem.particles.at(i);
		if(p->Position.y < ground) {
			p->Position.y = ground + (ground-p->Position.y);
			p->Velocity.y= -elasticity * p->Velocity.y;
			p->Velocity.x= (1-friction) * p->Velocity.x; // cheezy
			p->Velocity.z= (1-friction) * p->Velocity.z; // cheezy
		}
	}
}

void Cloth::Update(float windFactor, float ground) {
	//Compute forces
	//SpringDamper
	for( int i=0; i<springs.size(); ++i ) {
		springs.at(i)->ComputeForce();
	}

	/////////Aerodynamics
	Vector3 vair = Vector3(0, 0, -windFactor);	

	//update triangle normal/velocity/area
	for( int i=0; i<triangles.size(); ++i ) {
		triangles.at(i)->Update(vair);
	}
	//Calculate drag forces.
	ComputeAerodynamics(vair);

	//Collision detection
	CollisionGround(ground, 0, .05);


	//Change particle location
	float deltaTime = 0.02;
	//update particles
	//anchorType:	0 = two points
	//				1 = top edge
	psystem.Update(deltaTime, clothWidth+1, 1);

	
	//recalculate normal vectors.
	for(int i=0; i<triangles.size(); ++i) {
		Triangle * tri = triangles.at(i);
		Vector3 triNormal = tri->normal;

		tri->index1->avgNormals.push_back(triNormal);
		tri->index2->avgNormals.push_back(triNormal);
		tri->index3->avgNormals.push_back(triNormal);		
	}

	//Update vertex positions.
	for(int i=0; i<psystem.NumParticles; ++i) {
		Particle * p = psystem.particles.at(i);
		//Update position
		Vector3 pos = Vector3(p->Position.x, p->Position.y, p->Position.z);
		vertices.at(i)->setWeightPos(pos);			

		//update normals
		vertices.at(i)->calculateAveNormal();
	}
}


void Cloth::Draw(int drawStyle) {
	//draw style:	0 == wire frame
	//				1 == solid
	if( drawStyle == 0 ) {
		psystem.Draw();

		//draw springs
		for( int i=0; i<springs.size(); ++i ) {
			springs.at(i)->Draw();
		}
	}
	
	else if( drawStyle == 1 ) {	
		for( int i=0; i<triangles.size(); ++i ) {
			triangles.at(i)->Draw(Matrix34::IDENTITY);
		}
	}
}
