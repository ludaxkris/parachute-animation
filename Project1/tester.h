////////////////////////////////////////
// tester.h
////////////////////////////////////////

#ifndef CSE169_TESTER_H
#define CSE169_TESTER_H

#include "core.h"
#include "camera.h"
#include "cube.h"
#include "skel.h"
#include "skin.h"
#include "morph.h"
#include "animation.h"
#include "player.h"
#include "particle.h"
#include "particleSystem.h"
#include "cloth.h"
#include "ground.h"
#include "parachute.h"

////////////////////////////////////////////////////////////////////////////////

class Tester {
public:
	Tester(int argc,char **argv);
	~Tester();

	void Update();
	void Reset();
	void Draw();

	void Quit();

	// Event handlers
	void Resize(int x,int y);
	void Keyboard(int key,int x,int y);
	void MouseButton(int btn,int state,int x,int y);
	void MouseMotion(int x,int y);

	void selectJoint(GLint jointNum);
	void selectMorph(GLint morphNum);

	bool toggleSkeleton;
	bool toggleSkin;
	bool pauseAnimation;
	bool toggleGnd;

	int drawStyle;
	float windFactor;
	float gndDrawType;

	bool clothFirst; //determine if cloth or parachute

private:
	// Window management
	int WindowHandle;
	int DOFMenu, morphMenu;
	int WinX,WinY;

	// Input
	bool LeftDown,MiddleDown,RightDown;
	int MouseX,MouseY;

	// Components
	Camera Cam;
	//SpinningCube Cube;
	Skel skeleton;
	Skin skin;
	Morph mor;
	Animation anim;
	Cloth cloth;
	Player play;
	ParticleSystem psystem;
	Ground gnd;
	Parachute glide;



	Joint * jnt;
	Dof * morphDof;
};

////////////////////////////////////////////////////////////////////////////////

/*
The 'Tester' is a simple top level application class. It creates and manages a
window with the GLUT extension to OpenGL and it maintains a simple 3D scene
including a camera and some other components.
*/

#endif
