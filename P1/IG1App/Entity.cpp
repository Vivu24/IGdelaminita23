#include "Entity.h"

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
Abs_Entity::setTexture(std::string name) {
	Texture *t = new Texture(),
		*t2 = new Texture();
	//t->setWrap(GL_REPEAT);
	t->load(name, 255);
	//t2->setWrap(GL_REPEAT);
	//t2->load("../bmps/papelE.bmp", 255);
	mTexture = t;
	//mTexture2 = t2;
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
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		glColor4d(.0, .0, .0, .0);
	}
}

RGBTriangle::RGBTriangle(GLdouble radius)
	: Abs_Entity(), rotationVelocity(4.0)
{
	mMesh = Mesh::generateRGBTriangle(radius);
	mModelMat = translate(mModelMat, dvec3(200.0, .0, 1.0)); // Set inicial a la derecha
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
		//glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_BACK, GL_POINT);
		//glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		//glColor4d(.0, .0, .0, .0);
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
		//glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_BACK, GL_FILL);
		//glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		//glColor4d(.0, .0, .0, .0);
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
		//glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_BACK, GL_POINT);
		glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		glColor4d(.0, .0, .0, 1.0);
	}
}

RGBCube::RGBCube(GLdouble l)
	: Abs_Entity()
{
	mMesh = Mesh::generateRGBCubeTriangles(l);
	//setColor(.0, .0, .0, 1.0);
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
		//glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_BACK, GL_POINT);
		//glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		//glColor4d(.0, .0, .0, 1.0);
	}
}

Ground::Ground(GLdouble w, GLdouble h)
	: Abs_Entity()
{
	mMesh = Mesh::generateRectangleTexCor(w, h, 4, 4);
	mModelMat = rotate(dmat4(1), radians(-90.0), dvec3(1.0, 0.0, 0.0));

	//setTexture("../bmps/baldosaC.bmp");
}

Ground::~Ground()
{
	delete mMesh;
	mMesh = nullptr;
};

void
Ground::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mTexture->bind(GL_REPLACE);
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		mTexture->unbind();
		glLineWidth(1);
		//glColor4d(.0, .0, .0, 1.0);
	}
}

BoxOutline::BoxOutline(GLdouble l)
	: Abs_Entity()
{
	mMesh = Mesh::generateBoxOutlineTexCOr(l);
	//setTexture("../bmps/container.bmp");
}

BoxOutline::~BoxOutline()
{
	delete mMesh;
	mMesh = nullptr;
};

void
BoxOutline::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glEnable(GL_CULL_FACE);
		mTexture->bind(GL_REPLACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glCullFace(GL_BACK);
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		mTexture->unbind();
		mTexture2->bind(GL_REPLACE);
		glCullFace(GL_FRONT);
		mMesh->render();
		mTexture2->unbind();
		glLineWidth(1);
		glDisable(GL_CULL_FACE);
		//glColor4d(.0, .0, .0, 1.0);
	}
}

Star3D::Star3D(GLdouble re, GLuint np, GLdouble h)
{
	mMesh = Mesh::generateStar3DTexCor(re, np, h);

	setTexture("../bmps/baldosaP.bmp");
}

Star3D::~Star3D()
{
	delete mMesh;
	mMesh = nullptr;
};

void
Star3D::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		mTexture->bind(GL_REPLACE);
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();
		dmat4 rMat = mModelMat;
		rMat *= rotate(dmat4(1), radians(180.0), dvec3(0.0, 1.0, 0.0));
		aMat = modelViewMat * rMat; // glm matrix multiplication
		upload(aMat);
		mMesh->render();
		mTexture->unbind();
		glLineWidth(1);
	}
}