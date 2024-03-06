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

	gObjects.resize(0);
}
void
Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
	glDisable(GL_TEXTURE_2D);
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
		gObjects.push_back(new Ground(100, 100));
	}
	else if (id == 3) {
		gObjects.push_back(new BoxOutline(200.0));
	}
	else if (id == 4) {
		gObjects.push_back(new Star3D(200.0, 8.0, 200.0));
	}
	else if (id == 5) {
		gObjects.push_back(new GlassParapet());
	}
}
