////////////////////////////////////////
// parachute.cpp
////////////////////////////////////////


#include "core.h"
#include "parachute.h"



Parachute::Parachute() {

}


void Parachute::MakeParachute() {
	//Make cloth
	Vector3 initVert = Vector3(0, 0, 0);
	MakeCloth(20, 20, initVert, 0.3, 1); //horizontal
	MakeCube(20*.3);
	MakeRope(10, 20*.3);

	//Connect all 3 parts
	Particle *clothEdge1, *clothEdge2, *clothEdge3, *clothEdge4;
	clothEdge1 = psystem.particles.at(0);
	clothEdge2 = psystem.particles.at(clothWidth);
	clothEdge3 = psystem.particles.at(clothHeight*clothWidth);
	clothEdge4 = psystem.particles.at(clothHeight*(clothWidth+1)-1);

	//Springs
	SpringDamper * sdamp;
	float kspring = 0;
	float kdamp = 0;
	float restLength = .5;	

	//Cloth to rope
	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = clothEdge1;
	sdamp->P2 = topRope1;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = clothEdge2;
	sdamp->P2 = topRope3;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = clothEdge3;
	sdamp->P2 = topRope3;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = clothEdge4;
	sdamp->P2 = topRope4;
	springs.push_back(sdamp);

	//Rope to cube
	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = psystem.particles.at(psystem.NumParticles-4);
	sdamp->P2 = topCube1;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = psystem.particles.at(psystem.NumParticles-3);
	sdamp->P2 = topCube2;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = psystem.particles.at(psystem.NumParticles-2);
	sdamp->P2 = topCube3;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = psystem.particles.at(psystem.NumParticles-1);
	sdamp->P2 = topCube4;
	springs.push_back(sdamp);	

}

void Parachute::MakeCube(float size) {
	float mass = 0.1;

	Particle * p1 = new Particle(0, 0, 0);
	Particle * p2 = new Particle(size, 0, 0);
	Particle * p3 = new Particle(0, 0, size);
	Particle * p4 = new Particle(size, 0, size);
	Particle * p5 = new Particle(0, -size, 0); //bottom layer
	Particle * p6 = new Particle(size, -size, 0);
	Particle * p7 = new Particle(0, -size, size);
	Particle * p8 = new Particle(size, -size, size);

	p1->Mass = mass;
	p2->Mass = mass;
	p3->Mass = mass;
	p4->Mass = mass;
	p5->Mass = mass;
	p6->Mass = mass;
	p7->Mass = mass;
	p8->Mass = mass;

	psystem.particles.push_back( p1 );
	psystem.particles.push_back( p2 );
	psystem.particles.push_back( p3 );
	psystem.particles.push_back( p4 );
	psystem.particles.push_back( p5 ); //bottom layer
	psystem.particles.push_back( p6 );
	psystem.particles.push_back( p7 );
	psystem.particles.push_back( p8 );

	//center cube
	Vector3 translation = Vector3(-(size/2), 3, -(size/2));
	for(int i=psystem.NumParticles; i<psystem.NumParticles+8; ++i) {
		psystem.particles.at(i)->Position += translation;
	}

	psystem.NumParticles += 8;

	//Top of cube
	topCube1 = p1;
	topCube2 = p2;
	topCube3 = p3;
	topCube4 = p4;

	//Springs
	SpringDamper * sdamp;
	float kspring = 15;
	float kdamp = .055;
	float restLength = size;
	float crossRestlength = sqrtf( restLength * restLength * 2 );

	//face1
	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = p1;
	sdamp->P2 = p2;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = p2;
	sdamp->P2 = p3;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = p3;
	sdamp->P2 = p4;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = p1;
	sdamp->P2 = p4;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, crossRestlength);			
	sdamp->P1 = p1;
	sdamp->P2 = p3;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, crossRestlength);			
	sdamp->P1 = p2;
	sdamp->P2 = p4;
	springs.push_back(sdamp);

	//face2
	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = p5;
	sdamp->P2 = p6;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = p6;
	sdamp->P2 = p7;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = p7;
	sdamp->P2 = p8;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = p5;
	sdamp->P2 = p8;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, crossRestlength);			
	sdamp->P1 = p5;
	sdamp->P2 = p7;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, crossRestlength);			
	sdamp->P1 = p6;
	sdamp->P2 = p8;
	springs.push_back(sdamp);

	//Edges
	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = p1;
	sdamp->P2 = p5;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = p2;
	sdamp->P2 = p6;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = p3;
	sdamp->P2 = p7;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, restLength);			
	sdamp->P1 = p4;
	sdamp->P2 = p8;
	springs.push_back(sdamp);

	//face 3
	sdamp = new SpringDamper(kspring, kdamp, crossRestlength);			
	sdamp->P1 = p1;
	sdamp->P2 = p7;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, crossRestlength);			
	sdamp->P1 = p3;
	sdamp->P2 = p5;
	springs.push_back(sdamp);

	//face 4
	sdamp = new SpringDamper(kspring, kdamp, crossRestlength);			
	sdamp->P1 = p1;
	sdamp->P2 = p6;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, crossRestlength);			
	sdamp->P1 = p2;
	sdamp->P2 = p5;
	springs.push_back(sdamp);

	//face 5
	sdamp = new SpringDamper(kspring, kdamp, crossRestlength);			
	sdamp->P1 = p2;
	sdamp->P2 = p8;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, crossRestlength);			
	sdamp->P1 = p4;
	sdamp->P2 = p6;
	springs.push_back(sdamp);

	//face 6
	sdamp = new SpringDamper(kspring, kdamp, crossRestlength);			
	sdamp->P1 = p3;
	sdamp->P2 = p8;
	springs.push_back(sdamp);

	sdamp = new SpringDamper(kspring, kdamp, crossRestlength);			
	sdamp->P1 = p4;
	sdamp->P2 = p7;
	springs.push_back(sdamp);
}


void Parachute::MakeRope(int length, int clothSize) {

	Particle * part;
	float mass = .05;	

	for(int i=0; i<length; ++i) {
		part = new Particle(0, -0.3*i, 0);
		part->Mass;
		psystem.particles.push_back(part);

		part = new Particle(clothSize, -0.3*i, 0);
		part->Mass;
		psystem.particles.push_back(part);

		part = new Particle(0, -0.3*i, clothSize);
		part->Mass;
		psystem.particles.push_back(part);

		part = new Particle(clothSize, -0.3*i, clothSize);
		part->Mass;
		psystem.particles.push_back(part);
	}

	int numPart = psystem.NumParticles;
	psystem.NumParticles += length*4;

	//center rope
	Vector3 translation = Vector3(-(clothSize/2), 5, -(clothSize/2));
	for(int i=numPart; i<psystem.NumParticles; ++i) {
		psystem.particles.at(i)->Position += translation;
	}

	//Springs
	SpringDamper * sdamp;
	float kspring = 2;
	float kdamp = .01;
	float restLength = .3;
	

	for(int i=0; i<(length-1)*4; ++i) {
		sdamp = new SpringDamper(kspring, kdamp, restLength);			
		sdamp->P1 = psystem.particles.at(numPart+i);
		sdamp->P2 = psystem.particles.at(numPart+i+4);
		springs.push_back(sdamp);
	}

	//Top rope
	topRope1 = psystem.particles.at(numPart);
	topRope2 = psystem.particles.at(numPart+1);
	topRope3 = psystem.particles.at(numPart+2);
	topRope4 = psystem.particles.at(numPart+3);
}



void Parachute::MakeCloth(int width, int height, Vector3 initPosition, float triangleSize, int plane) {

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
	Vector3 translation = Vector3(-(width/2)*triangleSize, 5, -(height/2)*triangleSize);
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
	float kdamp = .03;

	float kspring2 = 20;
	float kdamp2 = .03;

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


//Density of air: 1.2 kg/m3
//drag coefficient: 1.8 for paper
void Parachute::ComputeAerodynamics(Vector3 vair) {
	float density = 1.2;
	float drag = 1;
	
	for( int i=0; i<triangles.size(); ++i ) {
		triangles.at(i)->ComputeAerodynamics(density, drag, vair);
	}
}

void Parachute::CollisionGround(float ground, float elasticity, float friction) {
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

void Parachute::Update(float windFactor, float ground) {
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
	psystem.Update(deltaTime, clothWidth+1, 2);

	
	//recalculate normal vectors.
	for(int i=0; i<triangles.size(); ++i) {
		Triangle * tri = triangles.at(i);
		Vector3 triNormal = tri->normal;

		tri->index1->avgNormals.push_back(triNormal);
		tri->index2->avgNormals.push_back(triNormal);
		tri->index3->avgNormals.push_back(triNormal);		
	}

	//Update vertex positions.
	float clothSize = (clothWidth+1) * (clothHeight+1);
	for(int i=0; i<clothSize; ++i) {
		Particle * p = psystem.particles.at(i);
		//Update position
		Vector3 pos = Vector3(p->Position.x, p->Position.y, p->Position.z);
		vertices.at(i)->setWeightPos(pos);			

		//update normals
		vertices.at(i)->calculateAveNormal();
	}
}


void Parachute::Draw(int drawStyle) {
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


void Parachute::DrawLines(Vertex * vert0, Vertex * vert1) {
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