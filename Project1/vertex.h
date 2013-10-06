////////////////////////////////////////
// vertex.h
////////////////////////////////////////

#ifndef CSE169_VERTEX_H
#define CSE169_VERTEX_H


#include "vector3.h"
#include <vector>


class Vertex {
public:
	Vertex();
	Vertex(float x, float y, float z);

	//Current Position
	Vector3 getPosVect();
	void setPosVect(Vector3 vect);
	float * getPosArray(float * vertArray);
	float * getWeightPosArray(float * vertArray);
	void setWeightPos(Vector3 vect);

	//Base Position
	Vector3 getBasePosVect();

	//Current Normal
	void setBaseNorm(float x, float y, float z);
	void setWeightNorm(Vector3 vect);
	void setNormVect(Vector3 vert);
	Vector3 getNormVect();
	float * getNormArray(float * vertArray);
	float * getWeightNormArray(float * vertArray);

	//Base Normal
	Vector3 getBaseNormVect();

	//Joint weights
	void setNumBind(int bind);
	void setJointBind(int jointNum);
	void setWeightBind(float weightBind);
	int getNumBind();
	int getJointBind(int jointNum);
	float getWeightBind(int weightNum);

	//Texture
	void setTexCoord(float x, float y);
	float * getTexCoord(float * texcoord);
	bool texcoord;

	//Cloth Normals
	void calculateAveNormal();
	std::vector <Vector3> avgNormals;

//private:
	Vector3 position;
	Vector3 normal;

	//float posx, posy, posz;
	//float normx, normy, normz;

	float texcoordX, texcoordY;

	Vector3 basePos;
	Vector3 baseNorm;

	Vector3 morphPos;
	Vector3 morphNorm;

	Vector3 weightNorm;
	Vector3 weightPos;

	int numBind;
	std::vector <int> joint;
	std::vector <float> weight;

	

};

#endif