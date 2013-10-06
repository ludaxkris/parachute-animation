////////////////////////////////////////
// skin.cpp
////////////////////////////////////////


#include "core.h"
#include "skin.h"
#include "matrix34.h"
#include "vector3.h"
#include "dof.h"
#include <vector>
#include "triangle.h"
#include "vertex.h"
#include "token.h"


Skin::Skin() {
	
}

bool Skin::Load(const char *file) {
	Tokenizer token;
	char temp[256];
	token.Open(file);	

	while(1) {
		token.GetToken(temp);

		//Vertices
		if(strcmp(temp,"positions") == 0) {
			//token.FindToken("positions");
			int numVert = token.GetInt();  //used to keep track of how many loops
			token.FindToken("{");	

			Vertex * vect;
			for(int i=0; i<numVert; ++i) {
				float x = token.GetFloat();
				float y = token.GetFloat();
				float z = token.GetFloat();

				vect = new Vertex(x, y, z);
				vertices.push_back(vect);
			}
			token.FindToken("}");
			continue;
		}

		//Normals
		else if(strcmp(temp,"normals") == 0) {
			//token.FindToken("normals");
			int numNorm = token.GetInt();  //used to keep track of how many loops
			token.FindToken("{");	
			
			for(int i=0; i<numNorm; ++i) {
				float x = token.GetFloat();
				float y = token.GetFloat();
				float z = token.GetFloat();
				(vertices.at(i))->setBaseNorm(x, y, z);
			}
			token.FindToken("}");
			continue;
		}

		//Texture Coordinates
		else if(strcmp(temp,"texcoords") == 0) {
			int numTexcoord = token.GetInt();  //used to keep track of how many loops
			token.FindToken("{");

			for(int i=0; i<numTexcoord; ++i) {
				float x = token.GetFloat();
				float y = token.GetFloat();
				(vertices.at(i))->setTexCoord(x, y);
				(vertices.at(i))->texcoord = true;
			}
			token.FindToken("}");
			continue;
		}

		//Weights
		else if(strcmp(temp,"skinweights") == 0) {
			//token.FindToken("skinweights");
			int numWeight = token.GetInt();  //used to keep track of how many loops
			token.FindToken("{");

			for(int i=0; i<numWeight; ++i) {
				int numBind = token.GetInt();
				(vertices.at(i))->setNumBind(numBind);

				for(int j=0; j<numBind; ++j) {
					int joint = token.GetInt();
					float weight = token.GetFloat();

					(vertices.at(i))->setJointBind(joint);
					(vertices.at(i))->setWeightBind(weight);
				}
			}
			token.FindToken("}");
			continue;
		}

		//Material Description
		else if(strcmp(temp,"material") == 0) {			
			token.FindToken("{");
			token.FindToken("texture");

			//Load image
			char filename[50];
			token.GetToken(filename);
			tx.LoadGLTextures(filename);

			token.FindToken("}");
			continue;
		}


		//Triangles
		else if(strcmp(temp,"triangles") == 0) {
			//token.FindToken("triangles");
			int numTri = token.GetInt();
			token.FindToken("{");	

			Triangle * tri;
			for(int i=0; i<numTri; ++i) {
				Vertex * vertx = vertices.at(token.GetInt());
				Vertex * verty = vertices.at(token.GetInt());
				Vertex * vertz = vertices.at(token.GetInt());

				tri = new Triangle(vertx, verty, vertz);
				triangles.push_back(tri);
			}
			token.FindToken("}");
			continue;
		}

			//Bindings
		else if(strcmp(temp,"bindings") == 0) {
			//token.FindToken("bindings");
			int numBind = token.GetInt();
			token.FindToken("{");
			
			for(int i=0; i<numBind; ++i) {
				token.FindToken("matrix");
				token.FindToken("{");
				float ax = token.GetFloat();
				float ay = token.GetFloat();
				float az = token.GetFloat();
				float bx = token.GetFloat();
				float by = token.GetFloat();
				float bz = token.GetFloat();
				float cx = token.GetFloat();
				float cy = token.GetFloat();
				float cz = token.GetFloat();
				float dx = token.GetFloat();
				float dy = token.GetFloat();
				float dz = token.GetFloat();
				
				Matrix34 bind = Matrix34(ax, bx, cx, dx,
				  ay, by, cy, dy,
				  az, bz, cz, dz);

				bind.Inverse();
				invBind.push_back(bind);

			}
			token.FindToken("}");
			continue;
		}
		else if(strcmp(temp,"}") ==0 ) {
			break;
		}
	}

	// Finish
	token.Close();
	return true;
}

bool Skin::LoadMorph(const char *file) {
	Morph * newMorph = new Morph();
	Dof * newDof = new Dof();

	Tokenizer token;
	char temp[256];
	token.Open(file);	

	while(1) {
		token.GetToken(temp);

		//Vertices
		if(strcmp(temp,"positions") == 0) {
			//token.FindToken("positions");
			newMorph->numVerts = token.GetInt();  //used to keep track of how many loops
			token.FindToken("{");	

			Vector3 vect;
			for(int i=0; i<newMorph->numVerts; ++i) {
				int ind = token.GetInt();	//index

				float x = token.GetFloat();
				float y = token.GetFloat();
				float z = token.GetFloat();

				vect = Vector3(x, y, z);

				newMorph->index.push_back(ind);
				newMorph->deltaPosition.push_back(vect);
			}
			token.FindToken("}");
			continue;
		}

		//Normals
		else if(strcmp(temp,"normals") == 0) {
			//token.FindToken("normals");			
			token.FindToken("{");	
			
			Vector3 vect;
			for(int i=0; i<newMorph->numVerts; ++i) {
				int ind = token.GetInt();	//index; throw this value away.

				float x = token.GetFloat();
				float y = token.GetFloat();
				float z = token.GetFloat();

				vect = Vector3(x, y, z);
				newMorph->deltaNormal.push_back(vect);
			}
			token.FindToken("}");
			continue;
		}
		else if(strcmp(temp,"}") == 0) {
			break;
		}
		else
			break;
	}

	token.Close();

	//add to the vector of morphs
	morphs.push_back(newMorph);
	dofs.push_back(newDof);

	return true;
}

//Skin::Update() (view independent processing)
//Compute skinning matrix for each joint: M=W·B-1 (you can
//	precompute and store B-1 instead of B)
//Loop through vertices and compute blended position & normal
void Skin::Update(Skel *skel) {

	//Compute all inverse bind matrices with worldMtx
	findBind(skel);

	//Use morph algorithm to find morph vectors (not for all vertices
	findMorph(skel);

	Matrix34 temp;
	Vector3 sumVectv, sumVectn;
	for( int i=0; i<vertices.size(); ++i ) {
		Vertex *vert = vertices.at(i);
		
		//reset vectors
		sumVectv = Vector3();
		sumVectn = Vector3();

		//Use skin algorithm to find skin vectors
		findSkin(sumVectv, sumVectn, vert);				
		
		vertices.at(i)->setWeightPos(sumVectv);
		sumVectn.Normalize();
		vertices.at(i)->setWeightNorm(sumVectn);
	}
}

void Skin::findMorph(Skel *skel) {
	//Vector3 sumVertv, sumVertn;
	for( int i=0; i<morphs.size(); ++i ) {
		Morph * morp = morphs.at(i);
		Dof * dofValue = dofs.at(i);
		for( int j=0; j<morp->numVerts; ++j ) {
			int index = morp->index.at(j);
			Vertex * baseVert = vertices.at(index);

			//Position
			Vector3 vtemp = morp->diffPosition(baseVert->getBasePosVect(), j);
			vtemp *= dofValue->getMorphValue();

			vtemp += baseVert->getBasePosVect();
			baseVert->setPosVect(vtemp);

			//Normal
			Vector3 ntemp = morp->diffPosition(baseVert->getBaseNormVect(), j);
			ntemp *= dofValue->getMorphValue();

			ntemp += baseVert->getBaseNormVect();
			baseVert->setNormVect(ntemp);
		}
	}
}


void Skin::findSkin(Vector3 & sumVectv, Vector3 & sumVectn, Vertex *vert) {
	int numJoints = vert->getNumBind();
	for( int j=0; j<numJoints; ++j ) {	
		//Position
		Vector3 vtemp;
		skinMatrix.at(vert->getJointBind(j)).Transform(vert->getPosVect(), vtemp);	//sum * position
		vtemp *= vert->getWeightBind(j);		//Wi * Bi-1 * weight
		sumVectv += vtemp;		//v'

		//Normal
		Vector3 ntemp;
		skinMatrix.at(vert->getJointBind(j)).Transform3x3(vert->getNormVect(), ntemp);
		ntemp *= vert->getWeightBind(j);		//Wi * Bi-1 * weight
		sumVectn += ntemp;		//n'
	}
}

void Skin::findBind(Skel * skel) {
	skinMatrix.clear();	//clear previous inverse bind matrices

	for(int i=0; i<invBind.size(); ++i) {
		Matrix34 worldMtx = skel->GetWorldMatrix(i);
		worldMtx.Dot(worldMtx, invBind.at(i));
		skinMatrix.push_back(worldMtx);
	}
}

//Set matrix state to Identity (world)
//Loop through triangles and draw using world space positions &
//	normals
void Skin::Draw(Skel * skel) {
	for( int i=0; i<triangles.size(); ++i ) {
		triangles.at(i)->Draw(skel->GetWorldMatrix(0));
	}
}

Dof * Skin::getMorph(int morphNum) {
	return dofs.at(morphNum);
}

int Skin::getNumMorph() {
	return dofs.size();
}