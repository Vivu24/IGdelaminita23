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

		if (vNormals.size() > 0) {
			// Activación de los vertex arrays
			glEnableClientState(GL_NORMAL_ARRAY);
			// Especificación del lugar y formato de los datos
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}
		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
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

	GLdouble d = l * 0.5;

	// 1
	mesh->vVertices.emplace_back(d, d, d);
	mesh->vVertices.emplace_back(-d, d, -d);
	mesh->vVertices.emplace_back(-d, d, d);

	// 2
	mesh->vVertices.emplace_back(d, d, d);
	mesh->vVertices.emplace_back(d, d, -d);
	mesh->vVertices.emplace_back(-d, d, -d);

	// 3
	mesh->vVertices.emplace_back(-d, -d, d);
	mesh->vVertices.emplace_back(d, d, d);
	mesh->vVertices.emplace_back(-d, d, d);

	// 4
	mesh->vVertices.emplace_back(-d, -d, d);
	mesh->vVertices.emplace_back(d, -d, d);
	mesh->vVertices.emplace_back(d, d, d);

	// 5
	mesh->vVertices.emplace_back(d, -d, d);
	mesh->vVertices.emplace_back(d, -d, -d);
	mesh->vVertices.emplace_back(d, d, d);

	// 6
	mesh->vVertices.emplace_back(d, -d, -d);
	mesh->vVertices.emplace_back(d, d, -d);
	mesh->vVertices.emplace_back(d, d, d);

	// 7
	mesh->vVertices.emplace_back(d, -d, -d);
	mesh->vVertices.emplace_back(-d, d, -d);
	mesh->vVertices.emplace_back(d, d, -d);

	// 8
	mesh->vVertices.emplace_back(d, -d, -d);
	mesh->vVertices.emplace_back(-d, -d, -d);
	mesh->vVertices.emplace_back(-d, d, -d);

	// 9
	mesh->vVertices.emplace_back(d, -d, -d);
	mesh->vVertices.emplace_back(d, -d, d);
	mesh->vVertices.emplace_back(-d, -d, d);

	// 10
	mesh->vVertices.emplace_back(d, -d, -d);
	mesh->vVertices.emplace_back(-d, -d, d);
	mesh->vVertices.emplace_back(-d, -d, -d);

	// 11
	mesh->vVertices.emplace_back(-d, -d, d);
	mesh->vVertices.emplace_back(-d, d, -d);
	mesh->vVertices.emplace_back(-d, -d, -d);

	// 12
	mesh->vVertices.emplace_back(-d, -d, d);
	mesh->vVertices.emplace_back(-d, d, d);
	mesh->vVertices.emplace_back(-d, d, -d);

	return mesh;
}

Mesh* 
Mesh::generateRGBCubeTriangles(GLdouble l)
{
	Mesh* mesh = generateCube(l);
	mesh->mPrimitive = GL_TRIANGLES;
	mesh->vColors.reserve(mesh->mNumVertices);

	// 1
	for (int i = 0; i < 6; ++i)
		mesh->vColors.emplace_back(.0, .0, 1.0, 1.0);

	// 2
	for (int i = 0; i < 6; ++i)
		mesh->vColors.emplace_back(1.0, .0, .0, 1.0);

	// 3
	for (int i = 0; i < 6; ++i)
		mesh->vColors.emplace_back(.0, 1.0, .0, 1.0);

	// 4
	for (int i = 0; i < 6; ++i)
		mesh->vColors.emplace_back(1.0, .0, .0, 1.0);

	// 5
	for (int i = 0; i < 6; ++i)
		mesh->vColors.emplace_back(.0, .0, 1.0, 1.0);

	// 6
	for (int i = 0; i < 6; ++i)
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

void IndexMesh::render() const {
// Comandos OpenGL para enviar datos de arrays a GPU
// Nuevos comandos para la tabla de índices
	if (vVertices.size() > 0) { // transfer data
		// transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());

		if (vIndexes != nullptr) {
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, vIndexes);
		}

		if (vColors.size() > 0) {             // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(
				4, GL_DOUBLE, 0, vColors.data()); // components number (rgba=4), type of
			// each component, stride, pointer
		}

		if (vNormals.size() > 0) {
			// Activación de los vertex arrays
			glEnableClientState(GL_NORMAL_ARRAY);
			// Especificación del lugar y formato de los datos
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}

		draw();
		glDisableClientState(GL_INDEX_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
}
// Comando para renderizar la malla indexada enviada
void IndexMesh::draw() const {
	glDrawElements(mPrimitive, nNumIndices,
		GL_UNSIGNED_INT, vIndexes);
}

IndexMesh* IndexMesh::generateIndexedBox(GLdouble l)
{
//#pragma region prueba1
//
//
//	const auto mesh = new IndexMesh();
//
//	mesh->mNumVertices = 8;
//
//	mesh->vVertices.reserve(mesh->mNumVertices);
//
//	mesh->vVertices.emplace_back(dvec3(-l / 2, l / 2, l / 2));
//
//	mesh->vVertices.emplace_back(dvec3(-l / 2, -l / 2, l / 2));
//
//	mesh->vVertices.emplace_back(dvec3(l / 2, l / 2, l / 2));
//
//	mesh->vVertices.emplace_back(dvec3(l / 2, -l / 2, l / 2));
//
//	mesh->vVertices.emplace_back(dvec3(l / 2, l / 2, -l / 2));
//
//	mesh->vVertices.emplace_back(dvec3(l / 2, -l / 2, -l / 2));
//
//	mesh->vVertices.emplace_back(dvec3(-l / 2, l / 2, -l / 2));
//
//	mesh->vVertices.emplace_back(dvec3(-l / 2, -l / 2, -l / 2));
//
//	mesh->nNumIndices = 36;
//	mesh->vIndexes = new GLuint[mesh->nNumIndices];
//
//	// cara de abajo
//	mesh->vIndexes[0] = 0;
//	mesh->vIndexes[1] = 3;
//	mesh->vIndexes[2] = 2;
//
//	mesh->vIndexes[3] = 0;
//	mesh->vIndexes[4] = 2;
//	mesh->vIndexes[5] = 1;
//
//	// cara de arriba
//	mesh->vIndexes[6] = 4;
//	mesh->vIndexes[7] = 5;
//	mesh->vIndexes[8] = 6;
//
//	mesh->vIndexes[9] = 4;
//	mesh->vIndexes[10] = 6;
//	mesh->vIndexes[11] = 7;
//
//	// cara lateral cercana izquierda
//	mesh->vIndexes[12] = 0;
//	mesh->vIndexes[13] = 4;
//	mesh->vIndexes[14] = 7;
//
//	mesh->vIndexes[15] = 0;
//	mesh->vIndexes[16] = 7;
//	mesh->vIndexes[17] = 3;
//
//	// cara lateral trasera derecha
//	mesh->vIndexes[18] = 1;
//	mesh->vIndexes[19] = 2;
//	mesh->vIndexes[20] = 6;
//
//	mesh->vIndexes[21] = 1;
//	mesh->vIndexes[22] = 6;
//	mesh->vIndexes[23] = 5;
//
//	// cara lateral cercana derecha
//	mesh->vIndexes[24] = 0;
//	mesh->vIndexes[25] = 1;
//	mesh->vIndexes[26] = 5;
//
//	mesh->vIndexes[27] = 0;
//	mesh->vIndexes[28] = 5;
//	mesh->vIndexes[29] = 4;
//
//	// cara lateral trasera izquierda
//	mesh->vIndexes[30] = 2;
//	mesh->vIndexes[31] = 3;
//	mesh->vIndexes[32] = 7;
//
//	mesh->vIndexes[33] = 2;
//	mesh->vIndexes[34] = 7;
//	mesh->vIndexes[35] = 6;
//
//	mesh->buildNormalVectors();
//
//	return mesh;
//#pragma endregion

#pragma region prueba2
	const auto mesh = new IndexMesh();

	mesh->mPrimitive = GL_TRIANGLES;
	/// VERTICES
	mesh->mNumVertices = 8;
	mesh->vVertices.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(l, l, -l); // v0
	mesh->vVertices.emplace_back(l, -l, -l); // v1
	mesh->vVertices.emplace_back(-l, -l, -l); // v2
	mesh->vVertices.emplace_back(-l, l, -l); // v3
	mesh->vVertices.emplace_back(l, l, l); // v4
	mesh->vVertices.emplace_back(l, -l, l); // v5
	mesh->vVertices.emplace_back(-l, -l, l); // v6
	mesh->vVertices.emplace_back(-l, l, l); // v7


	/// INDICES
	/// Define cuidadosamente los 36 índices que, de 3 en 3,
	/// determinan las 12 caras triangulares de la malla.
	/// Recuerda que los índices de estas caras deben darse
	/// en sentido ¡¡¡ANTI-HORARIO!!! según se mira el cubo desde su exterior
	mesh->nNumIndices = 36;
	mesh->vIndexes = new GLuint[mesh->nNumIndices];

	// cara de abajo
	mesh->vIndexes[0] = 0;
	mesh->vIndexes[1] = 3;
	mesh->vIndexes[2] = 2;

	mesh->vIndexes[3] = 0;
	mesh->vIndexes[4] = 2;
	mesh->vIndexes[5] = 1;

	// cara de arriba
	mesh->vIndexes[6] = 4;
	mesh->vIndexes[7] = 5;
	mesh->vIndexes[8] = 6;

	mesh->vIndexes[9] = 4;
	mesh->vIndexes[10] = 6;
	mesh->vIndexes[11] = 7;

	// cara lateral cercana izquierda
	mesh->vIndexes[12] = 0;
	mesh->vIndexes[13] = 4;
	mesh->vIndexes[14] = 7;

	mesh->vIndexes[15] = 0;
	mesh->vIndexes[16] = 7;
	mesh->vIndexes[17] = 3;

	// cara lateral trasera derecha
	mesh->vIndexes[18] = 1;
	mesh->vIndexes[19] = 2;
	mesh->vIndexes[20] = 6;

	mesh->vIndexes[21] = 1;
	mesh->vIndexes[22] = 6;
	mesh->vIndexes[23] = 5;

	// cara lateral cercana derecha
	mesh->vIndexes[24] = 0;
	mesh->vIndexes[25] = 1;
	mesh->vIndexes[26] = 5;

	mesh->vIndexes[27] = 0;
	mesh->vIndexes[28] = 5;
	mesh->vIndexes[29] = 4;

	// cara lateral trasera izquierda
	mesh->vIndexes[30] = 2;
	mesh->vIndexes[31] = 3;
	mesh->vIndexes[32] = 7;

	mesh->vIndexes[33] = 2;
	mesh->vIndexes[34] = 7;
	mesh->vIndexes[35] = 6;

	mesh->vColors.reserve(mesh->mNumVertices);
	for (int i = 0; i < mesh->mNumVertices; i++)
		mesh->vColors.emplace_back(0, 1, 0, 1);

	int nV = 3;
	mesh->vCaras.resize(mesh->nNumIndices / nV);
	for (int i = 0; i < mesh->nNumIndices / nV; i++)
	{
		mesh->vCaras[i] = Cara(
			mesh->vIndexes[i * nV],
			mesh->vIndexes[i * nV + 1],
			mesh->vIndexes[i * nV + 2]
		);
	}

	mesh->buildNormalVectors();

	return mesh;
#pragma endregion
}

glm::dvec3 IndexMesh::calculoVectorNormalPorNewell(Cara C) {
	glm::dvec3 n = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < C.numVertices; ++i) {
		auto vertActual = vVertices[C.getIndice(i)];
		auto vertSiguiente = vVertices[C.getIndice((i + 1) % C.numVertices)];
		n.x += (vertActual.y - vertSiguiente.y) * (vertActual.z + vertSiguiente.z);
		n.y += (vertActual.z - vertSiguiente.z) * (vertActual.x + vertSiguiente.x);
		n.z += (vertActual.x - vertSiguiente.x) * (vertActual.y + vertSiguiente.y);
	}
	return normalize(n);
}

void IndexMesh::buildNormalVectors()
{
	int i = 0;
	vNormals.resize(vCaras.size());
	for (const auto cara : vCaras)
	{
		vNormals[i] = calculoVectorNormalPorNewell(cara);
		i++;
	}
}
