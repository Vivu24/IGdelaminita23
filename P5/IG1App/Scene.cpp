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

	setScene(3);
}
void
Scene::freeObjects()
{ // release memory and resources
	for (Abs_Entity* el : gObjects) {
		delete el;
		el = nullptr;
	}

	delete dirLight;
	dirLight = nullptr;
	delete posLight;
	posLight = nullptr;
	delete spotLight;
	spotLight = nullptr;
	delete foco;
	foco = nullptr;

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
	//glEnable(GL_NORMALIZE);
	//glEnable(GL_LIGHTING);
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
	//glDisable(GL_NORMALIZE);
}

void 
Scene::loadTextures() {
	Texture* t = new Texture();
	t->load(textureRoot + imgs[0], 128);
	gTextures.push_back(t);
}

void Scene::setLights()
{
	glEnable(GL_LIGHTING);

	dirLight = new DirLight();
	fvec4 ambient = { 0, 0, 0, 1 };
	fvec4 diffuse = { 1, 1, 1, 1 };
	fvec4 specular = { 0.5, 0.5, 0.5, 1 };

	dirLight->setID(GL_LIGHT0);
	dirLight->setAmb(ambient);
	dirLight->setDiff(diffuse);
	dirLight->setSpec(specular);
	dirLight->setPosDir(fvec4(1, 1, 1, 0));

	posLight = new PosLight();
	diffuse = { 1, 1, 0, 1 };

	posLight->setID(GL_LIGHT1);
	posLight->setAmb(ambient);
	posLight->setDiff(diffuse);
	posLight->setSpec(specular);
	posLight->setPosDir(fvec3(100.0, 100.0, 0.0));

	spotLight = new SpotLight();
	diffuse = { 1, 1, 1, 1 };

	spotLight->setID(GL_LIGHT2);
	spotLight->setAmb(ambient);
	spotLight->setDiff(diffuse);
	spotLight->setSpec(specular);
	spotLight->setSpot(fvec3(.0, 100.0, 100.0), 180.0, 0.0);
}

void
Scene::render(Camera const& cam) const
{
	if (posLight != nullptr)
		posLight->upload(cam.viewMat());
	if (dirLight != nullptr)
		dirLight->upload(cam.viewMat());
	if (spotLight != nullptr)
		spotLight->upload(cam.viewMat());
	if (foco != nullptr)
		foco->upload(cam.viewMat());

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

	glDisable(GL_LIGHTING);

	freeObjects();
	glClearColor(0.6, 0.7, 0.8, 1.0);

	gObjects.push_back(new EjesRGB(400.0));

	if (id == 0) { // APARTADO 66
		EntityWithMaterial* sphere_0 = new RevSphere(150, 50, 50);
		sphere_0->setModelMat(translate(sphere_0->modelMat(), dvec3(0, 0, 300)));

		Material* m = new Material();
		m->setGold();
		sphere_0->setMaterial(m);

		EntityWithMaterial* sphere_1 = new RevSphere(150, 50, 50);
		sphere_1->setModelMat(translate(sphere_1->modelMat(), dvec3(300, 0, 0)));

		//sphere_1->setColor(1, 1, 0, 1);

		gObjects.push_back(sphere_0);
		gObjects.push_back(sphere_1);
	}
	else if (id == 1) {
		glClearColor(0, 0, 0, 1);

		setLights();

		foco = new SpotLight();
		fvec4 ambient = { 0, 0, 0, 1 };
		fvec4 diffuse = { 1, 1, 1, 1 };
		fvec4 specular = { 0.5, 0.5, 0.5, 1 };

		foco->setID(GL_LIGHT3);
		foco->setAmb(ambient);
		foco->setDiff(diffuse);
		foco->setSpec(specular);

		QuadricEntity* planeta = new Sphere(200.0);
		planeta->setModelMat(translate(dmat4(1), dvec3(0.0, -2200.0, .0)) * scale(dmat4(1), dvec3(10.0, 10.0, 10.0)));
		planeta->setRGB(1, 0.8, 0);

		CompoundEntity* node = new CompoundEntity();
		CompoundEntity* tie = new AdvancedTIE(gTextures[NOCHE]);
		node->addEntity(tie);
		node->setModelMat(glm::translate(node->modelMat(), dvec3(0, 0, 0)));
		foco->setSpot(node->pos + dvec3(0.0 , 100.0, 0.0), 180.0, 0.0);

		gObjects.push_back(planeta);
		gObjects.push_back(node);
	}
	else if (id == 2) {
		Abs_Entity* s = new IndexedBox(200.0);
		gObjects.push_back(s);
	}
	else if (id == 3) {
		Abs_Entity* toroide = new RevToroid(50.0, 100.0, 50.0, 50.0);
		toroide->setColor(1, 1, 1, 1);
		gObjects.push_back(toroide);
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

void Scene::enableDirLight()
{
	dirLight->enable();
}

void Scene::disableDirLight()
{
	dirLight->disable();
}

void Scene::enablePosLight()
{
	posLight->enable();
}

void Scene::disablePosLight()
{
	posLight->enable();
}

void Scene::enableSpotLight()
{
	spotLight->enable();
}

void Scene::disableSpotLight()
{
	spotLight->disable();
}

void Scene::enableFoco()
{
	foco->enable();
}

void Scene::disableFoco()
{
	foco->disable();
}

void Scene::moveTIELeft()
{
	gObjects[2]->setModelMat(translate(gObjects[2]->modelMat(), dvec3(0.0 , 0.0, 10.0)));
	foco->setSpot(gObjects[2]->pos + dvec3(0.0, 100.0, 0.0), 180.0, 0.0);
}

void Scene::moveTIERight()
{
	gObjects[2]->setModelMat(translate(gObjects[2]->modelMat(), dvec3(0.0, 0.0, -10.0)));
	foco->setSpot(gObjects[2]->pos + dvec3(0.0, 100.0, 0.0), 180.0, 0.0);
}
