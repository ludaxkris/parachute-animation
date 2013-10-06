////////////////////////////////////////
// skin.h
////////////////////////////////////////

#ifndef CSE169_SKIN_H
#define CSE169_SKIN_H

#include "token.h"
#include "matrix34.h"
#include "vector3.h"
#include "skel.h"
#include "triangle.h"
#include "vertex.h"
#include <vector>
#include "core.h"
#include "BMPImage.h"
#include "morph.h"



class Skin {
public:
	Skin();
	void Draw(Skel *skel);
	void Update(Skel *skel);
	void findBind(Skel *skel);
	void findMorph(Skel *skel);
	void findSkin(Vector3 & sumVectv, Vector3 & sumVectn, Vertex *vert);

	bool Load(const char *file);
	bool LoadMorph(const char *file);

	Dof * getMorph(int morphNum);
	int getNumMorph();

	BMPImage tx;

private:
	//Morphing
	std::vector <Morph*> morphs;
	std::vector <Dof*> dofs;

	//Skinning
	std::vector <Triangle*> triangles;
	std::vector <Vertex*> vertices;
	std::vector <Matrix34> invBind;
	std::vector <Matrix34> skinMatrix;
};

#endif