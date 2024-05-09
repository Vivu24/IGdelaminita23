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
	loadTextures();

	setScene(0);
}
void
Scene::freeObjects()
{ // release memory and resources
	for (Abs_Entity* el : gObjects) {
		delete el;
		el = nullptr;
	}

	gObjects.resize(0);
}
void
Scene::freeTextures() {
	for (Texture* t : gTextures) {
		delete t;
		t = nullptr;
	}
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
	glEnable(GL_COLOR_MATERIAL);		// Apartado 56
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_NORMALIZE);
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
	glDisable(GL_TEXTURE_2D);
	glDisable(GLUT_MULTISAMPLE);
	glDisable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);		// Apartado 56
	glDisable(GL_NORMALIZE);
}

void 
Scene::loadTextures() {
	Texture* t = new Texture();
	t->load(textureRoot + imgs[0], 128);
	gTextures.push_back(t);
}

void
Scene::render(Camera const& cam) const
{
	sceneDirLight(cam);		// Apartado 56

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

	orbit(10);
}

void 
Scene::sceneDirLight(Camera const& cam) const {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
}


void 
Scene::setScene(GLint id) {
	mId = id;

	freeObjects();

	glClearColor(0.6, 0.7, 0.8, 1.0);

	gObjects.push_back(new EjesRGB(400.0));

	if (id == 0) { // APARTADO 66
		CompoundEntity* inventedNode = new CompoundEntity();
		RGBTriangle* tr = new RGBTriangle(50.0);

		inventedNode->addEntity(tr);
		tr->setModelMat(glm::translate(inventedNode->modelMat(),
			dvec3(200, 0, 0)));

		gObjects.push_back(new RegularPolygon(100.0, 200.0, 1.0, 1.0, 1.0, 1.0));
		gObjects.push_back(new RGBRectangle(400.0, 150.0));
		gObjects.push_back(inventedNode);
	}
	else if (id == 1) {
		glClearColor(0, 0, 0, 1);
		QuadricEntity* planeta = new Sphere(200.0);
		planeta->setModelMat(translate(dmat4(1), dvec3(0.0, -2200.0, .0)) * scale(dmat4(1), dvec3(10.0, 10.0, 10.0)));
		planeta->setRGB(1, 0.8, 0);

		CompoundEntity* node = new CompoundEntity();
		CompoundEntity* tie = new AdvancedTIE(gTextures[NOCHE]);
		node->addEntity(tie);
		node->setModelMat(glm::translate(node->modelMat(), dvec3(0, 0, 0)));

		gObjects.push_back(planeta);
		gObjects.push_back(node);
	}
	else if (id == 2) {
		Abs_Entity* s = new IndexedBox(200.0);
		gObjects.push_back(s);
	}
}

void Scene::orbit(float time)
{
	if (mId == 1) {
		GLdouble speed = -8;

		rotY += speed * time;
		gObjects[1]->rot = dvec3(.0, .0, 1.0);
		gObjects[1]->ang = glm::radians(rotY);
	}
}
