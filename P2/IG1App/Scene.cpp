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
Scene::loadTextures() {
	gTextures.push_back(new Texture()); // Textura vacia para la foto mas adelante

	// Textura de la ventana
	Texture* t = new Texture();
	t->load(textureRoot + imgs[0], 128);
	gTextures.push_back(t);

	// Bucle de carga de las texturas con alpha = 255
	for (int i = 1; i < NUM_TEXTURES; ++i) {
		t = new Texture();
		t->load(textureRoot + imgs[i], 255);
		gTextures.push_back(t);
	}
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
	freeObjects();

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
		Abs_Entity* e = new Ground(300, 300);
		e->setTexture(gTextures[BALDOSA]);

		gObjects.push_back(e);
	}
	else if (id == 3) {
		Abs_Entity* e = new BoxOutline(200.0, dvec3(.0, .0, .0));
		e->setTexture(gTextures[CAJA_A]);
		e->setSecondTexture(gTextures[CAJA_B]);

		gObjects.push_back(e);
	}
	else if (id == 4) {
		Abs_Entity* e = new Star3D(200.0, 8.0, 200.0, dvec3(.0, .0, .0));
		e->setTexture(gTextures[ESTRELLA]);

		gObjects.push_back(e);
	}
	else if (id == 5) {
		Abs_Entity* e = new GlassParapet();
		e->setTexture(gTextures[VENTANA]);

		gObjects.push_back(e);
	}
	else if (id == 6) {
		Abs_Entity* e = new Ground(500.0, 500.0);
		e->setTexture(gTextures[BALDOSA]);

		Abs_Entity* p = new Photo();
		gTextures[FOTO]->loadColorBuffer(800.0, 600.0);
		p->setTexture(gTextures[FOTO]);

		gObjects.push_back(e);
		gObjects.push_back(p);
	}
	else if (id == 7) {
		// GROUND
		Abs_Entity* e = new Ground(300.0, 300.0);
		e->setTexture(gTextures[BALDOSA]);

		// PHOTO
		Abs_Entity* p = new Photo();
		gTextures[FOTO]->loadColorBuffer(800.0, 600.0);
		p->setTexture(gTextures[FOTO]);

		// BOX
		Abs_Entity* b = new BoxOutline(50.0, dvec3(-112.5, 25.0, -112.5));
		b->setTexture(gTextures[CAJA_A]);
		b->setSecondTexture(gTextures[CAJA_B]);

		// STAR
		Abs_Entity* s = new Star3D(25.0, 8.0, 25.0, dvec3(-112.5, 70.0, -112.5));
		s->setTexture(gTextures[ESTRELLA]);

		// GLASS
		Abs_Entity* gp = new GlassParapet();
		gp->setTexture(gTextures[VENTANA]);

		gObjects.push_back(e);
		gObjects.push_back(p);
		gObjects.push_back(b);
		gObjects.push_back(s);
		gObjects.push_back(gp);
	}
}
