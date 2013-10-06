////////////////////////////////////////
// vertex.cpp
////////////////////////////////////////


#include "vertex.h"
#include "vector3.h"
#include <vector>


Vertex::Vertex() {
	weightPos = basePos = Vector3(0, 0, 0);
	morphPos = Vector3(0, 0, 0);
	position = Vector3(0, 0, 0);
	texcoord = false;
}

Vertex::Vertex(float x, float y, float z) {
	weightPos = basePos = Vector3(x, y, z);
	morphPos = Vector3(x, y, z);
	position = Vector3(x, y, z);
	texcoord = false;
}

Vector3 Vertex::getPosVect() {
	return position;
}

void Vertex::setPosVect(Vector3 vect) {
	position = vect;
}

Vector3 Vertex::getBasePosVect() {
	return basePos;
}


float * Vertex::getPosArray(float * vertArray) {	
	vertArray[0] = position.x;
	vertArray[1] = position.y;
	vertArray[2] = position.z;
	return vertArray;
}

float * Vertex::getWeightPosArray(float * vertArray) {	
	vertArray[0] = weightPos.x;
	vertArray[1] = weightPos.y;
	vertArray[2] = weightPos.z;
	return vertArray;
}

void Vertex::setWeightPos(Vector3 vect) {
	weightPos = vect;
	//posx = vect.x;
	//posy = vect.y;
	//posz = vect.z;
}

void Vertex::setBaseNorm(float x, float y, float z) {
	baseNorm = Vector3(x, y, z);
	weightNorm = baseNorm;
	normal = Vector3(x, y, z);
}

void Vertex::setNormVect(Vector3 vert) {
	normal = vert;
}

Vector3 Vertex::getBaseNormVect() {
	return baseNorm;
}


void Vertex::setWeightNorm(Vector3 vect) {
	weightNorm = vect;
}

Vector3 Vertex::getNormVect() {
	return normal;
}

float * Vertex::getNormArray(float * vertArray) {	
	vertArray[0] = normal.x;
	vertArray[1] = normal.y;
	vertArray[2] = normal.z;
	return vertArray;
}

float * Vertex::getWeightNormArray(float * vertArray) {	
	vertArray[0] = weightNorm.x;
	vertArray[1] = weightNorm.y;
	vertArray[2] = weightNorm.z;
	return vertArray;
}

void Vertex::setNumBind(int bind) {
	numBind = bind;
}

void Vertex::setJointBind(int jointNum) {
	joint.push_back(jointNum);
}

void Vertex::setWeightBind(float weightBind) {
	weight.push_back(weightBind);
}

int Vertex::getNumBind() {
	return numBind;
}

int Vertex::getJointBind(int jointNum) {
	return joint.at(jointNum);
}

float Vertex::getWeightBind(int weightNum) {
	return weight.at(weightNum);
}

void Vertex::setTexCoord(float x, float y) {
	texcoordX = x;
	texcoordY = y;
}

float * Vertex::getTexCoord(float * texcoord) {
	texcoord[0] = texcoordX;
	texcoord[1] = texcoordY;
	return texcoord;
}

void Vertex::calculateAveNormal() {
	Vector3 avgNorm;
	for(int i=0; i<avgNormals.size(); ++i) {
		avgNorm += avgNormals.at(i);
	}
	avgNorm /= avgNormals.size();
	weightNorm = avgNorm.Normalize();
	avgNormals.clear();
}