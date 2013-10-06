////////////////////////////////////////
// morph.cpp
////////////////////////////////////////


#include "core.h"
#include "morph.h"
#include "matrix34.h"
#include "vector3.h"
#include "dof.h"
#include "token.h"

Morph::Morph() {

}

void Morph::Update() {
	
}

Vector3 Morph::diffPosition(Vector3 base, int index) {
	return deltaPosition.at(index) - base;
}

Vector3 Morph::diffNormal(Vector3 base, int index) {
	return deltaNormal.at(index) - base;
}