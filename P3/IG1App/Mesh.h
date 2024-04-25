#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include <vector>

#include "Cara.h"

class Mesh
{
public:
	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh
	static Mesh* generateRegularPolygon(GLuint num, GLdouble r);
	static Mesh* generateRGBTriangle(GLdouble r);
	static Mesh* generateRectangle(GLdouble w, GLdouble h);
	static Mesh* generateRGBRectangle(GLdouble w, GLdouble h);
	static Mesh* generateCube(GLdouble l);
	static Mesh* generateRGBCubeTriangles(GLdouble l);
	static Mesh* generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	static Mesh* generateBoxOutline(GLdouble l);
	static Mesh* generateBoxOutlineTexCOr(GLdouble l);
	static Mesh* generateStar3D(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h);

	Mesh() = default;
	virtual ~Mesh() = default;

	Mesh(const Mesh& m) = delete;            // no copy constructor
	Mesh& operator=(const Mesh& m) = delete; // no copy assignment

	virtual void render() const;

	GLuint size() const { return mNumVertices; }; // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };

protected:
	GLuint mPrimitive =
	  GL_TRIANGLES;          // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0; // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices; // vertex array
	std::vector<glm::dvec4> vColors;   // color array
	std::vector<glm::dvec2> vTexCoords;
	std::vector<glm::dvec3> vNormals;	// Apartado 61
	virtual void draw() const;
};

class IndexMesh : public Mesh {		// Apartado 62
protected:
	GLuint* vIndexes = nullptr; // tabla de índices
	GLuint nNumIndices = 0;
	std::vector<Cara> vCaras;
public:
	IndexMesh() { mPrimitive = GL_TRIANGLES; }
	~IndexMesh() { delete[] vIndexes; }
	virtual void render() const;
	virtual void draw() const;

	static IndexMesh* generateIndexedBox(GLdouble l);	// Apartado 63
	void buildNormalVectors();		// Apartado 65
	glm::dvec3 calculoVectorNormalPorNewell(Cara c);
};

#endif //_H_Scene_H_
