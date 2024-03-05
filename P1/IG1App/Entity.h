#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Texture.h"

class Abs_Entity // abstract class
{
public:
	Abs_Entity()
	  : mModelMat(1.0), mColor(1), mTexture() {}; // 4x4 identity matrix
	virtual ~Abs_Entity() = default;

	Abs_Entity(const Abs_Entity& e) = delete;            // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete; // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0; // abstract method
	virtual void update();

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	// Color setter and getter
	glm::dvec4 getColor() { return mColor; }
	void setColor(GLdouble r, GLdouble g, GLdouble b, GLdouble a);
	void setTexture(std::string name);

protected:
	Mesh* mMesh = nullptr; // the mesh
	glm::dmat4 mModelMat;  // modeling matrix

	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const;

	glm::dvec4 mColor;
	Texture* mTexture;
	Texture* mTexture2;
};

class EjesRGB : public Abs_Entity
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class RegularPolygon : public Abs_Entity 
{
public:
	explicit RegularPolygon(GLuint num, GLdouble radius, GLdouble r, GLdouble g, GLdouble b, GLdouble a);
	~RegularPolygon();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class RGBTriangle : public Abs_Entity
{
public:
	explicit RGBTriangle(GLdouble radius);
	~RGBTriangle();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void update() override;
private: 
	GLdouble rotationVelocity;
};

class RGBRectangle : public Abs_Entity
{
public:
	explicit RGBRectangle(GLdouble w, GLdouble h);
	~RGBRectangle();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};


class Cube : public Abs_Entity 
{
public:
	explicit Cube(GLdouble l);
	~Cube();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class RGBCube : public Abs_Entity
{
public:
	explicit RGBCube(GLdouble l);
	~RGBCube();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Ground : public Abs_Entity
{
public:
	explicit Ground(GLdouble w, GLdouble h);
	~Ground();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class BoxOutline : public Abs_Entity
{
public:
	explicit BoxOutline(GLdouble l);
	~BoxOutline();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Star3D : public Abs_Entity
{
public:
	explicit Star3D(GLdouble re, GLuint np, GLdouble h);
	~Star3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
#endif //_H_Entities_H_
