#include "Entity.h"
#include "IG1App.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Abs_Entity::upload(dmat4 const& modelViewMat) const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat)); // transfers modelView matrix to the GPU
}

void 
Abs_Entity::update() {}

void Abs_Entity::setColor(GLdouble r, GLdouble g, GLdouble b, GLdouble a) {
	mColor.r = r;
	mColor.g = g;
	mColor.b = b;
	mColor.a = a;
}

void 
Abs_Entity::setTexture(Texture* t) {
	mTexture = t;
}

void 
Abs_Entity::setSecondTexture(Texture* t) {
	mTexture2 = t;
}

EjesRGB::EjesRGB(GLdouble l)
  : Abs_Entity()
{
	mMesh = Mesh::createRGBAxes(l);
}

EjesRGB::~EjesRGB()
{
	delete mMesh;
	mMesh = nullptr;
};

void
EjesRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}

RegularPolygon::RegularPolygon(GLuint num, GLdouble radius, GLdouble r, GLdouble g, GLdouble b, GLdouble a)
	: Abs_Entity()
{
	mMesh = Mesh::generateRegularPolygon(num, radius);
	setColor(r, g, b, a);
}

RegularPolygon::~RegularPolygon()
{
	delete mMesh;
	mMesh = nullptr;
};

void
RegularPolygon::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
		glLineWidth(2);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		mMesh->render();

		glLineWidth(1);
		glColor4d(.0, .0, .0, .0);
	}
}

RGBTriangle::RGBTriangle(GLdouble radius)
	: Abs_Entity(), rotationVelocity(4.0)
{
	mMesh = Mesh::generateRGBTriangle(radius);
	//mModelMat = translate(mModelMat, dvec3(200.0, .0, 1.0)); // Set inicial a la derecha
	//setColor(r, g, b, a);
}

RGBTriangle::~RGBTriangle()
{
	delete mMesh;
	mMesh = nullptr;
};

void
RGBTriangle::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_POINT);

		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);
		glLineWidth(2);
		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
	}
}

void 
RGBTriangle::update() {
	mModelMat = rotate(dmat4(1), radians(rotationVelocity), dvec3(0.0, 0.0, 1.0))	  // Rotacion sobre el circulo
			  * translate(dmat4(1), dvec3(200.0, .0, 1.0))							  // Traslacion alredeor del circulo
		      * rotate(dmat4(1), radians(-rotationVelocity * 2), dvec3(.0, .0, 1.0)); // Rotacion sobre su propio eje

	rotationVelocity += .05;
}


RGBRectangle::RGBRectangle(GLdouble w, GLdouble h)
	: Abs_Entity()
{
	mMesh = Mesh::generateRGBRectangle(w, h);
	//setColor(r, g, b, a);
}

RGBRectangle::~RGBRectangle()
{
	delete mMesh;
	mMesh = nullptr;
};

void
RGBRectangle::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_FILL);
		glLineWidth(2);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
	}
}

Cube::Cube(GLdouble l)
	: Abs_Entity()
{
	mMesh = Mesh::generateCube(l);
	setColor(.0, .0, .0, 1.0);
}

Cube::~Cube()
{
	delete mMesh;
	mMesh = nullptr;
};

void
Cube::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_POINT);
		glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
		glLineWidth(2);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
		glColor4d(.0, .0, .0, 1.0);
	}
}

RGBCube::RGBCube(GLdouble l)
	: Abs_Entity()
{
	mMesh = Mesh::generateRGBCubeTriangles(l);
}

RGBCube::~RGBCube()
{
	delete mMesh;
	mMesh = nullptr;
};

void
RGBCube::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_POINT);
		glLineWidth(2);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
	}
}

Ground::Ground(GLdouble w, GLdouble h)
	: Abs_Entity()
{
	mMesh = Mesh::generateRectangleTexCor(w, h, 1, 1);
	//mModelMat = rotate(dmat4(1), radians(-90.0), dvec3(1.0, 0.0, 0.0));
}

Ground::~Ground()
{
	delete mMesh;
	mMesh = nullptr;
	mTexture = nullptr;
	mTexture2 = nullptr;
};

void
Ground::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mTexture->bind(GL_REPLACE);
		glLineWidth(2);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		mMesh->render();

		mTexture->unbind();
		glLineWidth(1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

BoxOutline::BoxOutline(GLdouble l, dvec3 p)
	: Abs_Entity()
{
	pos = p;
	mMesh = Mesh::generateBoxOutlineTexCOr(l);
	mModelMat = translate(dmat4(1), pos);
}

BoxOutline::~BoxOutline()
{
	delete mMesh;
	mMesh = nullptr;
	mTexture = nullptr;
	mTexture2 = nullptr;
};

void
BoxOutline::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
		glLineWidth(2);
		mTexture->bind(GL_REPLACE);
		glCullFace(GL_BACK);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		mMesh->render();

		mTexture->unbind();
		mTexture2->bind(GL_REPLACE);
		glCullFace(GL_FRONT);

		mMesh->render();

		mTexture2->unbind();
		glLineWidth(1);
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

Star3D::Star3D(GLdouble re, GLuint np, GLdouble h, dvec3 p) : rotationVelocity(4.0), Abs_Entity()
{
	pos = p;
	mMesh = Mesh::generateStar3DTexCor(re, np, h);
	mModelMat = translate(dmat4(1), pos);
}

Star3D::~Star3D()
{
	delete mMesh;
	mMesh = nullptr;
	mTexture = nullptr;
	mTexture2 = nullptr;
};

void
Star3D::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mTexture->bind(GL_REPLACE);
		glLineWidth(2);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		mMesh->render();

		aMat *= rotate(dmat4(1), radians(180.0), dvec3(0.0, 1.0, 0.0)); // glm matrix multiplication
		upload(aMat);
		mMesh->render();

		mTexture->unbind();
		glLineWidth(1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void
Star3D::update() {
	mModelMat = translate(dmat4(1), pos)
		* rotate(dmat4(1), radians(rotationVelocity), dvec3(0.0, 1.0, .0))
		* rotate(dmat4(1), radians(-rotationVelocity), dvec3(.0, .0, 1.0)); 

	rotationVelocity += .05;
}

GlassParapet::GlassParapet()
	: Abs_Entity()
{
	mMesh = Mesh::generateBoxOutlineTexCOr(300.0);
}

GlassParapet::~GlassParapet()
{
	delete mMesh;
	mMesh = nullptr;
	mTexture = nullptr;
	mTexture2 = nullptr;
};

void
GlassParapet::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mTexture->bind(GL_REPLACE);
		glLineWidth(2);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		mMesh->render();

		mTexture->unbind();
		glLineWidth(1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

Photo::Photo()
	: Abs_Entity()
{
	mMesh = Mesh::generateRectangleTexCor(150.0, 150.0, 1, 1);
	mModelMat = translate(dmat4(1), dvec3(0.0, 0.1, 0.0)) 
		* rotate(dmat4(1), radians(90.0), dvec3(1.0, 0.0, 0.0));
}

Photo::~Photo()
{
	delete mMesh;
	mMesh = nullptr;
	mTexture = nullptr;
	mTexture2 = nullptr;
};

void
Photo::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(2);
		mTexture->bind(GL_REPLACE);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		mMesh->render();

		mTexture->unbind();
		glLineWidth(1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void
Photo::update() {
	mTexture->loadColorBuffer(800.0, 600.0);
}

QuadricEntity::QuadricEntity() :
	red(),
	green(),
	blue()
{
	obj = gluNewQuadric();
}

QuadricEntity::~QuadricEntity()
{
	gluDeleteQuadric(obj);
}

void QuadricEntity::setRGB(GLdouble r, GLdouble g, GLdouble b)
{
	red = r;
	green = g;
	blue = b;
}

Sphere::Sphere(GLdouble r) :
	r(r)
{

}

Sphere::~Sphere()
{
	delete mMesh;
	mMesh = nullptr;
}

void Sphere::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
	upload(aMat);

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(red, green, blue);
	gluQuadricDrawStyle(obj, GLU_FILL);

	gluSphere(obj, r, 50, 50);
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

Cylinder::Cylinder(GLdouble rbase, GLdouble rtapa, GLdouble h) :
	rbase(rbase),
	rtapa(rtapa),
	h(h)
{

}

Cylinder::~Cylinder()
{
	delete mMesh;
	mMesh = nullptr;
}

void Cylinder::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
	upload(aMat);

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(red, green, blue);
	gluQuadricDrawStyle(obj, GLU_FILL);

	gluCylinder(obj, rbase, rtapa, h, 50, 50);
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

Disk::Disk(GLdouble rinterior, GLdouble rexterior) :
	rinterior(rinterior),
	rexterior(rexterior)
{

}

Disk::~Disk()
{
	delete mMesh;
	mMesh = nullptr;
}

void Disk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
	upload(aMat);

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(red, green, blue);
	gluQuadricDrawStyle(obj, GLU_FILL);

	gluDisk(obj, rinterior, rexterior, 50, 50);
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

PartialDisk::PartialDisk(GLdouble rinterior, GLdouble rexterior, GLdouble sang, GLdouble swang) :
	rinterior(rinterior),
	rexterior(rexterior),
	sang(sang),
	swang(swang)
{

}

PartialDisk::~PartialDisk()
{
	delete mMesh;
	mMesh = nullptr;
}

void PartialDisk::render(glm::dmat4 const& modelViewMat)
{
	dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
	upload(aMat);

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(red, green, blue);
	gluQuadricDrawStyle(obj, GLU_FILL);

	gluPartialDisk(obj, rinterior, rexterior, 50, 50, sang, swang);
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

CompoundEntity::CompoundEntity()
{
}

CompoundEntity::~CompoundEntity()
{
	for (auto& g : gObjects) {
		delete g;
		g = nullptr;
	}
}


void CompoundEntity::render(glm::dmat4 const& modelViewMat) const
{
	for (auto& g : gObjects) 
		g->render(modelViewMat);
}

void CompoundEntity::update()
{
	for (auto& e : gObjects) 
		e->update();
}

void CompoundEntity::addEntity(Abs_Entity* ae)
{
	gObjects.push_back(ae);
}

void CompoundEntity::setTexture(Texture* t)
{
	for (auto& e : gObjects)
		e->setTexture(t);
}

void CompoundEntity::setModelMat(glm::dmat4 const& aMat)
{
	for (auto& e : gObjects)
		e->setModelMat(aMat * e->modelMat());
}

IndexedBox::IndexedBox(GLdouble l) {
	mMesh = IndexMesh::generateIndexedBox(l);
}

IndexedBox::~IndexedBox()
{
	delete mMesh;
	mMesh = nullptr;
}

void IndexedBox::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);

		mMesh->render();
	}
}

WingAdvancedTIE::WingAdvancedTIE()
{
	Abs_Entity* r1 = new Ground(200.0, 100.0);
	Abs_Entity* r2 = new Ground(200.0, 100.0);
	Abs_Entity* r3 = new Ground(200.0, 100.0);

	r1->setModelMat(glm::translate(glm::dmat4(1), dvec3(0.0, 75.0, .0)) 
				* glm::translate(glm::dmat4(1), dvec3(0.0, .0, 25.0)) 
				* glm::rotate(glm::dmat4(1), radians(45.0), dvec3(1.0, .0, .0)));

	r3->setModelMat(glm::translate(glm::dmat4(1), dvec3(0.0, -75.0, .0))
				* glm::translate(glm::dmat4(1), dvec3(0.0, .0, 25.0))
				* glm::rotate(glm::dmat4(1), radians(-45.0), dvec3(1.0, .0, .0)));
	
	addEntity(r1);
	addEntity(r2);
	addEntity(r3);
}

WingAdvancedTIE::~WingAdvancedTIE()
{
	for (auto& g : gObjects) {
		delete g;
		g = nullptr;
	}
}

void WingAdvancedTIE::render(glm::dmat4 const& modelViewMat) const
{
	CompoundEntity::render(modelViewMat);
}

Morro::Morro()
{
	QuadricEntity* c = new Cylinder(20.0, 20.0, 70.0);
	QuadricEntity* d = new Disk(5.0, 20.0);

	c->setRGB(0, 0.25, 0.42);
	d->setRGB(0, 0.25, 0.42);

	addEntity(c);
	addEntity(d);
}

Morro::~Morro()
{
	for (auto& g : gObjects) {
		delete g;
		g = nullptr;
	}
}

void Morro::render(glm::dmat4 const& modelViewMat) const
{
	CompoundEntity::render(modelViewMat);
}

AdvancedTIE::AdvancedTIE(Texture* t)
{
	CompoundEntity* ala_1 = new WingAdvancedTIE();
	CompoundEntity* ala_2 = new WingAdvancedTIE();

	for (Abs_Entity* e : ala_2->objects()) {
		e->setModelMat(translate(dmat4(1), dvec3(0.0, 0.0, 300.0)) * scale(dmat4(1), dvec3(1.0, 1.0, -1.0)) * e->modelMat());
	}
	ala_1->setTexture(t);
	ala_2->setTexture(t);

	CompoundEntity* morro = new Morro();
	morro->setModelMat(translate(dmat4(1), dvec3(120.0, 0.0, 150.0))
					* glm::rotate(dmat4(1), radians(-90.0), dvec3(.0, 1.0, .0)));

	QuadricEntity* nucleo = new Sphere(100.0);
	nucleo->setModelMat(translate(dmat4(1), dvec3(0.0, 0.0, 150.0)));
	nucleo->setRGB(0, 0.25, 0.42);

	QuadricEntity* palo = new Cylinder(20.0, 20.0, 300.0);
	palo->setRGB(0, 0.25, 0.42);

	addEntity(ala_1);
	addEntity(ala_2);
	addEntity(morro);
	addEntity(nucleo);
	addEntity(palo);
}

AdvancedTIE::~AdvancedTIE()
{
	for (auto& g : gObjects) {
		delete g;
		g = nullptr;
	}
}

void AdvancedTIE::render(glm::dmat4 const& modelViewMat) const
{
	CompoundEntity::render(modelViewMat);
}

RevSphere::RevSphere(GLint r, GLint p, GLint m)
{
	dvec3* perfil = new dvec3[p];
	GLdouble alpha = 180.0 / (p - 1); 

	for (int i = 0; i < p; i++)
		perfil[i] = dvec3(cos(radians(alpha * i)) * r, sin(radians(alpha * i)) * r, 0);

	mMesh = MbR::generateIndexMbR(p, m, perfil);
}

RevSphere::~RevSphere()
{
	delete mMesh;
	mMesh = nullptr;
}

void RevSphere::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);

		mMesh->render();
	}
}
