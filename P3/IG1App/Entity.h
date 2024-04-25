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
	  : mModelMat(1.0), mColor(1), mTexture(), mTexture2() {}; // 4x4 identity matrix
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
	void setTexture(Texture* t);
	void setSecondTexture(Texture* t);

protected:
	glm::dvec3 pos;

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
	explicit BoxOutline(GLdouble l, glm::dvec3 p);
	~BoxOutline();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Star3D : public Abs_Entity
{
public:
	explicit Star3D(GLdouble re, GLuint np, GLdouble h, glm::dvec3 p);
	~Star3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void update() override;
private:
	GLdouble rotationVelocity;
};

class GlassParapet : public Abs_Entity
{
public:
	explicit GlassParapet();
	~GlassParapet();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Photo : public Abs_Entity
{
public:
	explicit Photo();
	~Photo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void update() override;
};

class QuadricEntity : public Abs_Entity		// Apartado 57
{
public:
	explicit QuadricEntity();
	~QuadricEntity();
	virtual void render(glm::dmat4 const& modelViewMat) const {};

	void setRGB(GLdouble r = 1.0, GLdouble g = 1.0, GLdouble b = 1.0);
protected:
	GLdouble red, green, blue;
	GLUquadricObj* obj;
};

class Sphere : public QuadricEntity		// Apartado 57
{
public:
	explicit Sphere(GLdouble r);
	~Sphere() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
private:
	GLdouble r;
};

class Cylinder : public QuadricEntity		// Apartado 57
{
public:
	explicit Cylinder(GLdouble rbase, GLdouble rtapa, GLdouble h);
	~Cylinder() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;

private:
	GLdouble rbase, rtapa, h;
};

class Disk : public QuadricEntity		// Apartado 57
{
public:
	explicit Disk(GLdouble rinterior, GLdouble rexterior);
	~Disk() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
private:
	GLdouble rinterior, rexterior;
};

class PartialDisk : public QuadricEntity		// Apartado 57
{
public:
	explicit PartialDisk(GLdouble rinterior, GLdouble rexterior, GLdouble sang, GLdouble swang);
	~PartialDisk() {};
	virtual void render(glm::dmat4 const& modelViewMat);
private:
	GLdouble rinterior, rexterior, sang, swang;
};

class CompoundEntity : public Abs_Entity 
{
public:
	explicit CompoundEntity();
	~CompoundEntity();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void update() override;

	void addEntity(Abs_Entity* ae);
private:
	std::vector<Abs_Entity*> gObjects;
};

class AdvancedTIE : public CompoundEntity
{

};

class WingAdvancedTIE : public Abs_Entity {
public:
	WingAdvancedTIE() {};
	~WingAdvancedTIE() {};
	virtual void render(glm::dmat4 const& modelViewMat) const override;
};

class IndexedBox : public Abs_Entity
{
public:
	explicit IndexedBox(GLdouble l);
	~IndexedBox();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	glm::vec3 calculoVectorNormalPorNewell(Cara c);
};
#endif //_H_Entities_H_
