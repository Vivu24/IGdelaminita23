#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

void
Mesh::draw() const
{
	glDrawArrays(
	  mPrimitive,
	  0,
	  size()); // primitive graphic, first index and number of elements to be rendered
}

void
Mesh::render() const
{
	if (vVertices.size() > 0) { // transfer data
		// transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
		glVertexPointer(
		  3, GL_DOUBLE, 0, vVertices.data()); // number of coordinates per vertex, type of
		                                      // each coordinate, stride, pointer
		if (vColors.size() > 0) {             // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(
			  4, GL_DOUBLE, 0, vColors.data()); // components number (rgba=4), type of
			                                    // each component, stride, pointer
		}

		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

Mesh*
Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* Mesh::generateRegularPolygon(GLuint num, GLdouble r) {
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_LINE_LOOP;
	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);

	for (int i = 0; i < num; i++) {
		double alpha = i * glm::radians(360.0 / num) + glm::radians(90.0);
		mesh->vVertices.emplace_back(r * glm::cos(alpha), r * glm::sin(alpha), 0.0);
	}

	return mesh;
}

Mesh* Mesh::generateRGBTriangle(GLdouble r) {
	Mesh* mesh = generateRegularPolygon(3, r);
	mesh->mPrimitive = GL_TRIANGLES;
	mesh->vColors.reserve(mesh->mNumVertices);

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* Mesh::generateRectangle(GLdouble w, GLdouble h) {
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = 4;
	mesh->vVertices.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(-w / 2, h / 2, 0.0);
	mesh->vVertices.emplace_back(-w / 2, -h / 2, 0.0);
	mesh->vVertices.emplace_back(w / 2, h / 2, 0.0);
	mesh->vVertices.emplace_back(w / 2, -h / 2, 0.0);

	return mesh;
}

Mesh* Mesh::generateRGBRectangle(GLdouble w, GLdouble h) {
	Mesh* mesh = generateRectangle(w, h);
	mesh->vColors.reserve(mesh->mNumVertices);

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

	return mesh;
}

Mesh* Mesh::generateCube(GLdouble l) {
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLES;
	mesh->mNumVertices = 36;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// 1
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, l / 2);

	// 2
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);

	// 3
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, l / 2);

	// 4
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);

	// 5
	mesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);

	// 6
	mesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);

	// 7
	mesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);

	// 8
	mesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);

	// 9
	mesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);

	// 10
	mesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);

	// 11
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);

	// 12
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);

	return mesh;
}

Mesh* 
Mesh::generateRGBCubeTriangles(GLdouble l)
{
	Mesh* mesh = generateCube(l);
	mesh->mPrimitive = GL_TRIANGLES;
	mesh->vColors.reserve(mesh->mNumVertices);

	// 1
	mesh->vColors.emplace_back(.0, .0, 1.0, 1.0);
	mesh->vColors.emplace_back(.0, .0, 1.0, 1.0);
	mesh->vColors.emplace_back(.0, .0, 1.0, 1.0);

	mesh->vColors.emplace_back(.0, .0, 1.0, 1.0);
	mesh->vColors.emplace_back(.0, .0, 1.0, 1.0);
	mesh->vColors.emplace_back(.0, .0, 1.0, 1.0);

	// 2
	mesh->vColors.emplace_back(1.0, .0, .0, 1.0);
	mesh->vColors.emplace_back(1.0, .0, .0, 1.0);
	mesh->vColors.emplace_back(1.0, .0, .0, 1.0);

	mesh->vColors.emplace_back(1.0, .0, .0, 1.0);
	mesh->vColors.emplace_back(1.0, .0, .0, 1.0);
	mesh->vColors.emplace_back(1.0, .0, .0, 1.0);

	// 3
	mesh->vColors.emplace_back(.0, 1.0, .0, 1.0);
	mesh->vColors.emplace_back(.0, 1.0, .0, 1.0);
	mesh->vColors.emplace_back(.0, 1.0, .0, 1.0);

	mesh->vColors.emplace_back(.0, 1.0, .0, 1.0);
	mesh->vColors.emplace_back(.0, 1.0, .0, 1.0);
	mesh->vColors.emplace_back(.0, 1.0, .0, 1.0);

	// 4
	mesh->vColors.emplace_back(1.0, .0, .0, 1.0);
	mesh->vColors.emplace_back(1.0, .0, .0, 1.0);
	mesh->vColors.emplace_back(1.0, .0, .0, 1.0);

	mesh->vColors.emplace_back(1.0, .0, .0, 1.0);
	mesh->vColors.emplace_back(1.0, .0, .0, 1.0);
	mesh->vColors.emplace_back(1.0, .0, .0, 1.0);

	// 5
	mesh->vColors.emplace_back(.0, .0, 1.0, 1.0);
	mesh->vColors.emplace_back(.0, .0, 1.0, 1.0);
	mesh->vColors.emplace_back(.0, .0, 1.0, 1.0);

	mesh->vColors.emplace_back(.0, .0, 1.0, 1.0);
	mesh->vColors.emplace_back(.0, .0, 1.0, 1.0);
	mesh->vColors.emplace_back(.0, .0, 1.0, 1.0);

	// 6
	mesh->vColors.emplace_back(.0, 1.0, .0, 1.0);
	mesh->vColors.emplace_back(.0, 1.0, .0, 1.0);
	mesh->vColors.emplace_back(.0, 1.0, .0, 1.0);

	mesh->vColors.emplace_back(.0, 1.0, .0, 1.0);
	mesh->vColors.emplace_back(.0, 1.0, .0, 1.0);
	mesh->vColors.emplace_back(.0, 1.0, .0, 1.0);

	return mesh;
}

Mesh* Mesh::generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* mesh = generateRectangle(w, h);
	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(rw, 0.0);
	mesh->vTexCoords.emplace_back(0.0, 0.0);
	mesh->vTexCoords.emplace_back(rw, rh);
	mesh->vTexCoords.emplace_back(0.0, rh);

	return mesh;
}

Mesh* Mesh::generateBoxOutline(GLdouble l)
{
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble d = l * 0.5;

	mesh->vVertices.emplace_back(-d, d, d);
	mesh->vVertices.emplace_back(-d, -d, d);
	mesh->vVertices.emplace_back(d, d, d);
	mesh->vVertices.emplace_back(d, -d, d);

	mesh->vVertices.emplace_back(d, d, -d);
	mesh->vVertices.emplace_back(d, -d, -d);

	mesh->vVertices.emplace_back(-d, d, -d);
	mesh->vVertices.emplace_back(-d, -d, -d);

	mesh->vVertices.emplace_back(-d, d, d);
	mesh->vVertices.emplace_back(-d, -d, d);

	return mesh;
}

Mesh* Mesh::generateBoxOutlineTexCOr(GLdouble l)
{
	Mesh* mesh = generateBoxOutline(l);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	for (int i = 0; i < 2; ++i) {
		mesh->vTexCoords.emplace_back(0.0, 0.0);
		mesh->vTexCoords.emplace_back(0.0, -1.0);
		mesh->vTexCoords.emplace_back(1.0, 0.0);
		mesh->vTexCoords.emplace_back(1.0, -1.0);
	}

	mesh->vTexCoords.emplace_back(0.0, 0.0);
	mesh->vTexCoords.emplace_back(0.0, -1.0);

	return mesh;
}

Mesh* Mesh::generateStar3D(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_FAN;
    mesh->mNumVertices = (2 * np) + 2;
    mesh->vVertices.reserve(mesh->mNumVertices);

    GLdouble outerLength = re;
    GLdouble innerLength = re / 2;

    mesh->vVertices.emplace_back(0.0, 0.0, 0.0);

    for (int i = 0; i < np * 2; i++) {

		GLdouble auxI = i;
		GLdouble alpha = (auxI / 2) * radians(360.0 / np) + radians(90.0);

        if (i % 2 == 0) {
            mesh->vVertices.emplace_back(outerLength * cos(alpha), outerLength * sin(alpha), h);
        } else {
			mesh->vVertices.emplace_back(innerLength * cos(alpha), innerLength * sin(alpha), h);
        }
    }
    mesh->vVertices.push_back(mesh->vVertices[1]);

    return mesh;
}

Mesh* 
Mesh::generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h) {
	Mesh* mesh = generateStar3D(re, np, h);
	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(0.5, 0.5);
	
	for (int i = 0; i < 4; ++i) {
		mesh->vTexCoords.emplace_back(0.0, 1.0);
		mesh->vTexCoords.emplace_back(0.5, 1.0);
		mesh->vTexCoords.emplace_back(0.0, 1.0);
		mesh->vTexCoords.emplace_back(0.0, 0.5);
	}

	mesh->vTexCoords.emplace_back(0.0, 1.0);

	return mesh;
}
