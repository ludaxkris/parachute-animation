////////////////////////////////////////
// joint.h
////////////////////////////////////////

#ifndef CSE169_MORPH_H
#define CSE169_MORPH_H

#include "token.h"
#include "matrix34.h"
#include "vector3.h"
#include "dof.h"
#include <vector>


class Morph {
public:
	Morph();

	//void Load(const char *file);
	Vector3 diffPosition(Vector3 base, int index);
	Vector3 diffNormal(Vector3 base, int index);

	void Update();

	int numVerts;
	std::vector<int> index;
	std::vector<Vector3> deltaPosition;
	std::vector<Vector3> deltaNormal;
};

#endif
