#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

using namespace std;

// static single instance (singleton pattern)

IG1App IG1App::s_ig1app; // default constructor (constructor with no parameters)

void
IG1App::close()
{
	if (!mStop) { // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop(); // stops main loop and destroy the OpenGL context
		mStop = true;        // main loop stopped
	}
	free();
}

void
IG1App::run() // enters the main event processing loop
{
	if (mWinId == 0) {      // if not initialized
		init();         // initialize the application
		glutMainLoop(); // enters the main event processing loop
		mStop = true;   // main loop has stopped
	}
}

void
IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context
	// allocate memory and resources
	mViewPort =
	  new Viewport(mWinW, mWinH); // glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera = new Camera(mViewPort);
	mScene = new Scene;

	mCamera->set3D();
	mScene->init();
}

void
IG1App::iniWinOpenGL()
{ // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);                   // GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH); // window size
	// glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE |
	                    GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth
	                                                    // buffer and stencil buffer

	mWinId = glutCreateWindow(
	  "IG1App"); // with its associated OpenGL context, return window's identifier

	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);

	glutMouseFunc(s_mouse);
	glutMotionFunc(s_motion);
	glutMouseWheelFunc(s_mouseWheel);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}
void
IG1App::free()
{ // release memory and resources
	delete mScene;
	mScene = nullptr;
	delete mCamera;
	mCamera = nullptr;
	delete mViewPort;
	mViewPort = nullptr;
}

void 
IG1App::start() {
	glutIdleFunc(s_update);
}

void 
IG1App::stop() {
	glutIdleFunc(NULL);
}

void
IG1App::update() {
	mScene->update();
	glutPostRedisplay();
}

void
IG1App::display() /*const*/
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer

	if (m2Vistas) {
		display2V();
	}
	else {
		mViewPort->setSize(mWinW, mWinH);
		mViewPort->setPos(0, 0);
		mScene->render(*mCamera); // uploads the viewport and camera to the GPU
	}

	glutSwapBuffers(); // swaps the front and back buffer
}

void
IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth;
	mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}

void
IG1App::key(unsigned char key, int x, int y)
{
	bool need_redisplay = true;

	switch (key) {
		case 27:                     // Escape key
			glutLeaveMainLoop(); // stops main loop and destroy the OpenGL context
			break;
		case '+':
			mCamera->setScale(+0.01); // zoom in  (increases the scale)
			break;
		case '-':
			mCamera->setScale(-0.01); // zoom out (decreases the scale)
			break;
		case 'l':
			mCamera->set3D();
			break;
		case 'o':
			mCamera->set2D();
			break;
		case '1':
			stop();
			mScene->setScene(0);
			mCamera->set3D();
			break;
		case '2':
			stop();
			mScene->setScene(1);
			mCamera->set3D();
			break;
		case '3': 
			stop();
			mScene->setScene(2);
			mCamera->set3D();
			break;
		case '4': 
			stop();
			mScene->setScene(3);
			mCamera->set3D();
			break;
		case '5':
			stop();
			mScene->setScene(4);
			mCamera->set3D();
			break;
		case '6':
			stop();
			mScene->setScene(5);
			mCamera->set3D();
			break;
		case 'u':
			mScene->update();
			break;
		case 'U':
			start();
			break;
		case 'p': // APARTADO 44
			mCamera->changePrj();
			break;
		case 'k':
			m2Vistas = !m2Vistas;
			break;
		/*case 'a' : // COMENTADO PARA QUE NO HAYA CONFLICTO CON LAS LETRAS DE LAS LUCES
			mCamera->moveLR(1);
			break;
		case 's' :
			mCamera->moveUD(1);
			break;
		case 'd' :
			mCamera->moveLR(-1);
			break;
		case 'c':
			mCamera->moveUD(-1);
			break;*/
		case 'q':
			mScene->enableDirLight();
			break;
		case 'w':
			mScene->disableDirLight();
			break;
		case 'a':
			mScene->enablePosLight();
			break;
		case 's':
			mScene->disablePosLight();
			break;
		case 'z':
			mScene->enableSpotLight();
			break;
		case 'x':
			mScene->disableSpotLight();
			break;
		case 'f':
			mScene->moveTIELeft();
			break;
		case 'g':
			mScene->moveTIERight();
			break;
		default:
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to
		                     // display()
}

void
IG1App::specialKey(int key, int x, int y)
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	switch (key) {
		case GLUT_KEY_RIGHT:
			//mCamera->pitch(-1); // rotates -1 on the X axis
			//mCamera->moveLR(-1);
			//mCamera->pitchReal(1);
			//mCamera->pitch(1); // rotates 1 on the X axis
			//mCamera->moveLR(-1);
			//mCamera->pitchReal(1);

			mCamera->yawReal(-1);
			break;
		case GLUT_KEY_LEFT:
			//mCamera->yaw(1); // rotates 1 on the Y axis
			//mCamera->moveFB(1);
			mCamera->yawReal(1);
			//mCamera->yaw(-1); // rotate -1 on the Y axis
			//mCamera->yawReal(-1);
			break;
		case GLUT_KEY_UP:
			//mCamera->roll(1); // rotates 1 on the Z axis
			//mCamera->moveUD(1);
			mCamera->pitchReal(1);
			break;
		case GLUT_KEY_DOWN:
			//mCamera->roll(-1); // rotates -1 on the Z axis
			//mCamera->moveUD(-1);
			mCamera->pitchReal(-1);
			break;
		default:
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to
		                     // display()
}

void IG1App::display2V()
{
	Camera auxCam = *mCamera;	// Camara auxiliar copiando mCamera
	Viewport auxVP = *mViewPort;	// Viewport auxiliar

	mViewPort->setSize(mWinW / 2, mWinH);
	auxCam.setSize(mViewPort->width(), mViewPort->height());

	//*mViewPort = auxVP;

	mViewPort->setPos(0, 0);
	mScene->render(auxCam);

	mViewPort->setPos(mWinW / 2, 0);
	auxCam.setCenital();
	mScene->render(auxCam);
}

void IG1App::mouse(int button, int state, int x, int y)
{
	mInitialMouseCoord = glm::vec2(x, y);
	mMouseButt = button;
}

void IG1App::motion(int x, int y)
{
	mMouseCoord = glm::vec2(x, y);

	if (mMouseButt == 2) {	// Click Der
		mCamera->moveLR(mInitialMouseCoord.x - x);
		mCamera->moveUD(-mInitialMouseCoord.y + y);
	}
	else if (mMouseButt == 0){	// Click Izq
		mCamera->orbit((mInitialMouseCoord.x - x) * 0.1, mInitialMouseCoord.y - y);
	}

	mInitialMouseCoord = mMouseCoord;

	glutPostRedisplay();
}

void IG1App::mouseWheel(int n, int d, int x, int y)
{
	int auxmodifiers = glutGetModifiers();

	if (auxmodifiers == GLUT_ACTIVE_CTRL) {
		mCamera->setScale(d * 0.01);
	}
	else if (auxmodifiers == 0) {
		mCamera->moveFB(d * 5);
	}

	glutPostRedisplay();
}





