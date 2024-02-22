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
	mModelMat = translate(dmat4(1), dvec3(200.0, .0, .0));
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
		dmat4 aMat = modelViewMat * rotate(dmat4(1), radians(-rotationVelocity), dvec3(0.0, 0.0, 1.0))
			* translate(mModelMat, dvec3(.0, .0, 200.0)) 
			* rotate(dmat4(1), radians(rotationVelocity * 2), dvec3(.0, .0, 1.0));
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		//glColor4d(.0, .0, .0, .0);
	}
}

void 
RGBTriangle::update() {
	//// Rotación sobre sí mismo
	//glm::dmat4 rot = 

	//glm::dmat4 initTrans = 

	//// Rotación sobre el círculo
	//glm::dmat4 rot2 = 

	//moveMat = rot2 * initTrans * rot;

	rotationVelocity -= .05;
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
		glPolygonMode(GL_FRONT, GL_FILL);
		//glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
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
