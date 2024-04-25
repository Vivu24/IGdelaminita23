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
		glClearColor(1, 0, 0, 1);
		QuadricEntity* planeta = new Sphere(200.0);
		planeta->setRGB(255, 233, 0);
		gObjects.push_back(planeta);
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
	else if (id == 8) {
		//Abs_Entity* s = new Sphere(100.0);
		Abs_Entity* s = new IndexedBox(200.0);
		gObjects.push_back(s);
	}
}
