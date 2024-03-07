#include "Scene.h"
#include "CheckML.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Scene::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures
	
	setScene(0);
}
void
Scene::free()
{ // release memory and resources

	for (Abs_Entity* el : gObjects) {
		delete el;
		el = nullptr;
	}
	for (Texture* t : gTextures) {
		delete t;
		t = nullptr;
	}

	gTextures.resize(0);
	gObjects.resize(0);
}
void
Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
	glEnable(GL_TEXTURE_2D);
	glEnable(GLUT_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
	glDisable(GL_TEXTURE_2D);
	glDisable(GLUT_MULTISAMPLE);
	glDisable(GL_BLEND);
}

void
Scene::render(Camera const& cam) const
{
	cam.upload();

	for (Abs_Entity* el : gObjects) {
		el->render(cam.viewMat());
	}
}

void 
Scene::update() {
	for (Abs_Entity* e : gObjects) {
		e->update();
	}
}

void 
Scene::setScene(GLint id) {
	free();

	gObjects.push_back(new EjesRGB(400.0));

	if (id == 0) {
		gObjects.push_back(new RegularPolygon(100.0, 200.0, 1.0, 1.0, 1.0, 1.0));
		gObjects.push_back(new RGBRectangle(400.0, 150.0));
		gObjects.push_back(new RGBTriangle(50.0));
	}
	else if (id == 1) {
		gObjects.push_back(new RGBCube(200.0));
	}
	else if (id == 2) {
		Texture* t = new Texture();
		t->load("../bmps/baldosaC.bmp", 255);
		gTextures.push_back(t);
		Abs_Entity* e = new Ground(100, 100);
		e->setTexture(t);
		gObjects.push_back(e);
	}
	else if (id == 3) {
		Texture* t = new Texture();
		t->load("../bmps/container.bmp", 255);
		gTextures.push_back(t);
		Texture* t2 = new Texture();
		t2->load("../bmps/papelE.bmp", 255);
		gTextures.push_back(t2);
		Abs_Entity* e = new BoxOutline(200.0);
		e->setTexture(t);
		e->setSecondTexture(t2);
		gObjects.push_back(e);
	}
	else if (id == 4) {
		Texture* t = new Texture();
		t->load("../bmps/baldosaP.bmp");
		gTextures.push_back(t);
		Abs_Entity* e = new Star3D(200.0, 8.0, 200.0);
		e->setTexture(t);
		gObjects.push_back(e);
	}
	else if (id == 5) {
		Texture* t = new Texture();
		t->load("../bmps/windowV.bmp", 128);
		gTextures.push_back(t);
		Abs_Entity* e = new GlassParapet();
		e->setTexture(t);
		gObjects.push_back(e);
	}
}
