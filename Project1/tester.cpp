////////////////////////////////////////
// tester.cpp
////////////////////////////////////////

#include "tester.h"
#include "matrix34.h"
#include <stdio.h>
#include <string>

#define WINDOWTITLE	"Chris Tung CSE 169 Project 4"

////////////////////////////////////////////////////////////////////////////////

static Tester *TESTER;

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	TESTER = new Tester(argc,argv);
	glutMainLoop();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

// These are really HACKS to make glut call member functions instead of static functions
static void display()									{TESTER->Draw();}
static void idle()										{TESTER->Update();}
static void resize(int x,int y)							{TESTER->Resize(x,y);}
static void keyboard(unsigned char key,int x,int y)		{TESTER->Keyboard(key,x,y);}
static void mousebutton(int btn,int state,int x,int y)	{TESTER->MouseButton(btn,state,x,y);}
static void mousemotion(int x, int y)					{TESTER->MouseMotion(x,y);}
//static void DOFEdit(GLint jointNum)						{TESTER->selectJoint(jointNum);}
//static void MorphEdit(GLint morphNum)					{TESTER->selectMorph(morphNum);}

////////////////////////////////////////////////////////////////////////////////

Tester::Tester(int argc,char **argv) {
	
	WinX=640;
	WinY=480;
	LeftDown=MiddleDown=RightDown=false;
	MouseX=MouseY=0;

	// Create the window
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( WinX, WinY );
	glutInitWindowPosition( 0, 0 );
	WindowHandle = glutCreateWindow( WINDOWTITLE );
	glutSetWindowTitle( WINDOWTITLE );
	glutSetWindow( WindowHandle );

	// Background color
	glClearColor( 0., 0., 0., 1. );

	// Callbacks
	glutDisplayFunc( display );
	glutIdleFunc( idle );
	glutKeyboardFunc( keyboard );
	glutMouseFunc( mousebutton );
	glutMotionFunc( mousemotion );
	glutPassiveMotionFunc( mousemotion );
	glutReshapeFunc( resize );


	// Initialize components
	//char * file;
	//char * file2;
	/*char * file3;*/
	//if( argc != 3 ) {//default file
	//	file = "test.skel";
	//	file2 = "test.skin";
	//}
	//else 
	//if( argc >= 4) {	//includes morph
	//	file = argv[1];
	//	file2 = argv[2];
	//	file3 = argv[3];
	//}
	//else {	//skel and skin only
	//	file = argv[1];
	//	file2 = argv[2];
	//}


	//Load Skeleton
	//skeleton.Load(argv[1]);
	////Load Skin
	//skin.Load(argv[2]);

	//if( argc >= 4) { //If more than skel and skin
	//	for( int i=3; i<argc; ++i ) {
	//		std::string str = argv[i];

	//		if(str.find(".morph", 0) != std::string::npos)	//Load Morph					
	//			skin.LoadMorph(argv[i]);
	//		
	//		else if(str.find(".anim", 0) != std::string::npos) //Load Animation
	//			anim.Load(argv[i]);			
	//	}
	//}

/////////////////////////////////////////////////////////Project 3
	//skeleton.Load("wasp.skel");
	////Load Skin
	//skin.Load("wasp.skin");

	//anim.Load("wasp_walk.anim");



	////Create new menu for select joints
	//DOFMenu = glutCreateMenu(DOFEdit);
	//
	//int numJnt = skeleton.numberJoints();
	//for(int i=0; i<numJnt; ++i) {
	//	char jointStr[20];
	//	sprintf( jointStr, "Joint %d", (i+1));		
	//	glutAddMenuEntry(jointStr, i);
	//}
	//
	//glutAttachMenu(GLUT_MIDDLE_BUTTON);

	////Initialize Joint
	//jnt = skeleton.getJoint(0);


	//morphMenu = glutCreateMenu(MorphEdit);
	//if(skin.getNumMorph() > 0) {
	//	//Create new menu for select Morph Dof		
	//	int numMorph = skin.getNumMorph();
	//	for(int i=0; i<numMorph; ++i) {
	//		char morphStr[20];
	//		sprintf( morphStr, "Morph %d", (i+1));		
	//		glutAddMenuEntry(morphStr, i);
	//	}
	//	
	//	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//	//Initialize Joint
	//	morphDof = skin.getMorph(0);
	//}

	//toggleSkeleton = true; //true = draw skeleton
	//toggleSkin = true;
	//pauseAnimation = false;

	////Precompute keyframes
	//anim.Precompute();
	//play.setClip(anim);

	////set play time
	//play.setTime(-100, 100);
	//play.setSpeed(.01);
/////////////////////////////////////////////////////////

	//Project4
	Vector3 vect(0, 0, 0);
	cloth.createCloth(20, 20, vect, .3, 0); //xy plane
	gnd.MakeGround(20, -5); //ground starts far away

	pauseAnimation = false;
	gndDrawType = 0;		//don't draw gnd
	toggleGnd = false;

	windFactor = 0;	//wind starts off
	drawStyle = 1; //default draw solid

	//Parachute
	glide.MakeParachute();
	clothFirst = true;

	Cam.SetAspect(float(WinX)/float(WinY));

	float diff[] = {0, 0, 0, 1};
	float spec[] = {1, 1, 1, 1};
	float amb[] = {0, .5, 1, 1};
	float pos[] = {0, 10, -60, 1};
	
	//Extra
	//glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 
	glEnable(GL_DEPTH_TEST);

	glLightfv( GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv( GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv( GL_LIGHT0, GL_POSITION, pos);


	float diff2[] = {0, .2, .5, 1};
	float amb2[] = {0, .5, 1, 1};
	float pos2[] = {10, 40, 40, 1};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1); 
	glEnable(GL_DEPTH_TEST);

	glLightfv( GL_LIGHT1, GL_DIFFUSE, diff2);
	glLightfv( GL_LIGHT1, GL_AMBIENT, amb2);
	glLightfv( GL_LIGHT1, GL_POSITION, pos2);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

}

////////////////////////////////////////////////////////////////////////////////

Tester::~Tester() {
	glFinish();
	glutDestroyMenu(morphMenu);
	glutDestroyMenu(DOFMenu);
	glutDestroyWindow(WindowHandle);
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Update() {
	// Update the components in the world
	Cam.Update();
	//Cube.Update();

	//if(!pauseAnimation) {
	//	play.Update();	
	//	skeleton.updatePose(play.getPose());
	//}

	//skeleton.Update();	

	//skin.Update(&skeleton);

	if(!pauseAnimation) {
		if(clothFirst) {			//draw cloth
			if(toggleGnd)
				cloth.Update(windFactor, gnd.getPositionY());
			else			//Turn off gnd
				cloth.Update(windFactor, -100);
		}
		
		else {						//draw parachute			
			if(toggleGnd)
				glide.Update(windFactor, gnd.getPositionY());
			else			//Turn off gnd
				glide.Update(windFactor, -100);
		}
	}


	// Tell glut to re-display the scene
	//glutSetMenu(morphMenu);
	//glutSetMenu(DOFMenu);
	glutSetWindow(WindowHandle);
	glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Reset() {
	Cam.Reset();
	Cam.SetAspect(float(WinX)/float(WinY));

	//Cube.Reset();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Draw() {

	// Begin drawing scene
	glViewport(0, 0, WinX, WinY);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw components
	Cam.Draw();		// Sets up projection & viewing matrices
	//Cube.Draw();

	////call to skeleton's draw
	//if(toggleSkeleton)
	//	skeleton.Draw();

	////draw skin
	//if(toggleSkin)
	//	skin.Draw(&skeleton);
	if(toggleGnd)
		gnd.Draw(gndDrawType);

	
	if(clothFirst)				//draw cloth
		cloth.Draw(drawStyle);
	else						//draw parachute
		glide.Draw(0);

	

	// Finish drawing scene
	glFinish();
	glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Quit() {
	glFinish();
	glutDestroyWindow(WindowHandle);
	//glutDestroyMenu(DOFMenu);
	//glutDestroyMenu(morphMenu);
	exit(0);
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Resize(int x,int y) {
	WinX = x;
	WinY = y;
	Cam.SetAspect(float(WinX)/float(WinY));
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Keyboard(int key,int x,int y) {
	float rotateAmount = .1;
	float rotateNegAmount = -.1;
	float speedAmount = .01;
	float negSpeedAmount = -.01;
	float translateAmount = 0.1;
	float rotateClothRad = 0.1;
	Matrix34 rotMtx = Matrix34::IDENTITY;

	switch(key) {
		case 0x1b:		// Escape
			Quit();
			break;
	//	case 'r':
	//		Reset();
	//		break;

	////---DOF Modifications
	//	//case 'z':		//Increase Dof X
	//	//	jnt->dofx.increaseValue(rotateAmount);
	//	//	break;
	//	//case 'x':		//Decrease Dof X
	//	//	jnt->dofx.increaseValue(rotateNegAmount);
	//	//	break;
	//	//case 'c':		//Increase Dof Y
	//	//	jnt->dofy.increaseValue(rotateAmount);
	//	//	break;
	//	//case 'v':		//Decrease Dof Y
	//	//	jnt->dofy.increaseValue(rotateNegAmount);
	//	//	break;
	//	//case 'b':		//Increase Dof Z
	//	//	jnt->dofz.increaseValue(rotateAmount);
	//	//	break;
	//	//case 'n':		//Decrease Dof Z
	//	//	jnt->dofz.increaseValue(rotateNegAmount);
	//	//	break;

	////-----Image Modifications.
	//	case 't':		//Toggle Skeleton Draw
	//		toggleSkeleton = !toggleSkeleton;
	//		break;
	//	case 'y':		//Toggle Skin Draw
	//		toggleSkin = !toggleSkin;
	//		break;

	////------Morph Modifications.
	//	case 'k':		//Decrease Morph
	//		morphDof->increaseMorph(rotateNegAmount);
	//		break;
	//	case 'l':		//Increase Morph
	//		morphDof->increaseMorph(rotateAmount);
	//		break;

	////------Animation Modifications.
	//	case 'p':		//Pause Animation
	//		pauseAnimation = !pauseAnimation;
	//		break;
	//	case 'i':		//Decrease Speed
	//		play.increaseSpeed(negSpeedAmount);
	//		break;
	//	case 'o':		//Increase Speed
	//		play.increaseSpeed(speedAmount);
	//		break;



		case 'p':		//Pause Animation
			pauseAnimation = !pauseAnimation;
			break;

	//Parachute
		case 'o':		//toggle between cloth and parachute
			clothFirst = !clothFirst;
			break;


	//Cloth Modifications.
		case 'f':		//Switch to solid
			drawStyle = 1;
			break;
		case 'g':		//Switch to wire
			drawStyle = 0;
			break;
		case 'a':		//Move left
			cloth.translateCloth(Vector3(-translateAmount, 0, 0));
			break;
		case 'd':		//Move right
			cloth.translateCloth(Vector3(translateAmount, 0, 0));
			break;
		case 'w':		//Move forward
			cloth.translateCloth(Vector3(0, 0, -translateAmount));
			break;
		case 's':		//Move backward
			cloth.translateCloth(Vector3(0, 0, translateAmount));
			break;
		case 'v':		//Move up
			cloth.translateCloth(Vector3(0, translateAmount, 0));
			break;
		case 'b':		//Move down
			cloth.translateCloth(Vector3(0, -translateAmount, 0));
			break;
		case 'q':		//rotate X counterclock wise
			rotMtx.MakeRotateX(rotateClothRad);
			cloth.rotateCloth(rotMtx);
			break;
		case 'e':		//rotate X clock wise
			rotMtx.MakeRotateX(-rotateClothRad);
			cloth.rotateCloth(rotMtx);
			break;
		case 'r':		//rotate Y counterclock wise
			rotMtx.MakeRotateY(rotateClothRad);
			cloth.rotateCloth(rotMtx);
			break;
		case 't':		//rotate Y clock wise
			rotMtx.MakeRotateY(-rotateClothRad);
			cloth.rotateCloth(rotMtx);
			break;
		case 'y':		//rotate Z counterclock wise
			rotMtx.MakeRotateZ(rotateClothRad);
			cloth.rotateCloth(rotMtx);
			break;
		case 'u':		//rotate Z clock wise
			rotMtx.MakeRotateZ(-rotateClothRad);
			cloth.rotateCloth(rotMtx);
			break;



	//Wind adjustments
		case 'm':		//toggle wind
			if(windFactor != 0)	//on turn off
				windFactor = 0;
			else
				windFactor = 20;	//off turn on
			break;
		case 'h':		//Increase wind
			windFactor += 1;
			break;
		case 'j':
			windFactor -= 1;
			break;

	//Ground adjustments
		case 'z':		//toggle ground
			toggleGnd = !toggleGnd;
			break;
		case 'x':		//raise ground
			gnd.setPositionY(gnd.getPositionY() + 0.5);	
			break;
		case 'c':		//lower ground
			gnd.setPositionY(gnd.getPositionY() - 0.5);	
			break;
		case 'k':		//Draw Solid
			gndDrawType = 0;	
			break;
		case 'l':		//Draw Wire
			gndDrawType = 1;	
			break;





	}
}

////////////////////////////////////////////////////////////////////////////////

void Tester::MouseButton(int btn,int state,int x,int y) {
	if(btn==GLUT_LEFT_BUTTON) {
		LeftDown = (state==GLUT_DOWN);
	}
	else if(btn==GLUT_MIDDLE_BUTTON) {
		MiddleDown = (state==GLUT_DOWN);
	}
	else if(btn==GLUT_RIGHT_BUTTON) {
		RightDown = (state==GLUT_DOWN);
	}
}

////////////////////////////////////////////////////////////////////////////////

void Tester::MouseMotion(int nx,int ny) {
	int dx = nx - MouseX;
	int dy = -(ny - MouseY);

	MouseX = nx;
	MouseY = ny;

	// Move camera
	// NOTE: this should really be part of Camera::Update()
	if(LeftDown) {
		const float rate=1.0f;
		Cam.SetAzimuth(Cam.GetAzimuth()+dx*rate);
		Cam.SetIncline(Cam.GetIncline()-dy*rate);
	}
	if(RightDown) {
		const float rate=0.01f;
		Cam.SetDistance(Cam.GetDistance()*(1.0f-dx*rate));
	}
}

////////////////////////////////////////////////////////////////////////////////

void Tester::selectJoint(GLint jointNum) {
	jnt = skeleton.getJoint((int)jointNum);
}

void Tester::selectMorph(GLint morphNum) {
	morphDof = skin.getMorph((int)morphNum);
}