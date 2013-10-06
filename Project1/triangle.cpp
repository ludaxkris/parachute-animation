////////////////////////////////////////
// triangle.cpp
////////////////////////////////////////


#include "core.h"
#include "triangle.h"
#include "matrix34.h"
#include "vector3.h"


Triangle::Triangle() {
	index1 = 0;
	index2 = 0;
	index3 = 0;
}

Triangle::Triangle(Vertex * x, Vertex * y, Vertex * z) {
	index1 = x;
	index2 = y;
	index3 = z;
}

Triangle::Triangle(Particle * x, Particle * y, Particle * z) {
	part1 = x;
	part2 = y;
	part3 = z;
}

Triangle::Triangle(Vertex * x, Vertex * y, Vertex * z, Particle * xp, Particle * yp, Particle * zp) {
	index1 = x;
	index2 = y;
	index3 = z;
	part1 = xp;
	part2 = yp;
	part3 = zp;
}

void Triangle::Update(Vector3 vair) {
	Vector3 cross;
	//update velocity and triangle normals
	velocity = (part1->Velocity + part2->Velocity + part3->Velocity) / 3;
	velocity -= vair;

	//normals
	//2-1 * 3-1
	Vector3 a = part2->Position - part1->Position;
	Vector3 b = part3->Position - part1->Position;
	cross.Cross(a, b);

	//check for division by 0
	if(cross.Mag2() != 0)
		normal = cross.Normalize();
	else
		normal = cross;

	//figure out which side of the normal to use.
	float doubleNormal = normal.Dot(vair);
	if( doubleNormal >= -1 && doubleNormal < 0 ) {
		//do nothing
	}
	else {
		normal = normal.Negate();
	}


	//area
	float area0 = cross.Mag() * .5;

	//check if velocity is 0
	Vector3 vel = velocity;
	if( velocity.Mag2() != 0 )
		vel = velocity.Normalize();

	area = vel.Dot(normal) * area0;
}

void Triangle::ComputeAerodynamics(float density, float drag, Vector3 vair) {
	float aero = -.5 * density * drag;
	
	Vector3 force = aero * velocity.Mag2() * area * normal;

	//apply 1/3 of the force to each particle
	part1->ApplyForce(force/3);
	part2->ApplyForce(force/3);
	part3->ApplyForce(force/3);
}


void Triangle::Draw(Matrix34 worldMtx) {
	float ind1[3], ind2[3], ind3[3];
	float norm1[3], norm2[3], norm3[3];
	
	//normal.convertToArray(norm1);
	//normal.convertToArray(norm2);
	//normal.convertToArray(norm3);

	float tex1[2], tex2[2], tex3[2];
	if(index1->texcoord) {
		//glBindTexture(GL_TEXTURE_2D, 1);
        
	}
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(Matrix34::IDENTITY);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);

	if(index1->texcoord)
		glTexCoord2fv(index1->getTexCoord(tex1));
	glNormal3fv(index1->getWeightNormArray(norm1));
	//glNormal3fv(norm1);
	glVertex3fv(index1->getWeightPosArray(ind1)); 

	if(index2->texcoord)
		glTexCoord2fv(index2->getTexCoord(tex2));
	glNormal3fv(index2->getWeightNormArray(norm2));
	//glNormal3fv(norm2);
	glVertex3fv(index2->getWeightPosArray(ind2)); 

	if(index3->texcoord)
		glTexCoord2fv(index3->getTexCoord(tex3));
	glNormal3fv(index3->getWeightNormArray(norm3));
	//glNormal3fv(norm3);
	glVertex3fv(index3->getWeightPosArray(ind3));
	
	glEnd();

}

//Draw using particle positions
void Triangle::Draw() {
	float ind1[3], ind2[3], ind3[3];
	float norm1[3], norm2[3], norm3[3];

	float tex1[2], tex2[2], tex3[2];
	if(index1->texcoord) {
		//glBindTexture(GL_TEXTURE_2D, 1);
        
	}

	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(Matrix34::IDENTITY);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);

	if(index1->texcoord)
		glTexCoord2fv(index1->getTexCoord(tex1));
	glNormal3fv(index1->getWeightNormArray(norm1));
	glVertex3fv(part1->Position.convertToArray(ind1)); 

	if(index2->texcoord)
		glTexCoord2fv(index2->getTexCoord(tex2));
	glNormal3fv(index2->getWeightNormArray(norm2));
	glVertex3fv(part2->Position.convertToArray(ind2)); 

	if(index3->texcoord)
		glTexCoord2fv(index3->getTexCoord(tex3));
	glNormal3fv(index3->getWeightNormArray(norm3));
	glVertex3fv(part3->Position.convertToArray(ind3));
	
	glEnd();

}