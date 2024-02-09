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
	: Abs_Entity()
{
	mMesh = Mesh::generateRGBTriangle(radius);
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
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		//glColor4d(.0, .0, .0, .0);
	}
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
