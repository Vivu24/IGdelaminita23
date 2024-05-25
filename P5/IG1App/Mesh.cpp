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
		//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		//glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
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

		if (vTexCoords.size() > 0) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
		}

		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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

		if (vTexCoords.size() > 0) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
		}

		draw();
		glDisableClientState(GL_INDEX_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}
// Comando para renderizar la malla indexada enviada
void IndexMesh::draw() const {
	glDrawElements(mPrimitive, nNumIndices,
		GL_UNSIGNED_INT, vIndexes);
}

IndexMesh* IndexMesh::generateIndexedBox(GLdouble l)
{
	const auto mesh = new IndexMesh();

	mesh->mPrimitive = GL_TRIANGLES;
	mesh->mNumVertices = 8;
	mesh->vVertices.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(-l, l, l); 
	mesh->vVertices.emplace_back(-l, -l, l); 
	mesh->vVertices.emplace_back(l, l, l); 
	mesh->vVertices.emplace_back(l, -l, l); 
	mesh->vVertices.emplace_back(l, l, -l); 
	mesh->vVertices.emplace_back(l, -l, -l); 
	mesh->vVertices.emplace_back(-l, l, -l); 
	mesh->vVertices.emplace_back(-l, -l, -l);

	mesh->nNumIndices = 36;
	mesh->vIndexes = new GLuint[mesh->nNumIndices];

	const GLuint arr[36] =
	{
		0, 1, 2, 1, 3, 2, 2, 3, 4,
		3, 5, 4, 4, 5, 6, 5, 7, 6,

		//6, 7, 0, 7, 1, 0,

		0, 6, 1, 6, 7, 1,
		0, 2, 4, 4, 6, 0, 1, 5, 3, 1, 7, 5
	};
	for (int i = 0; i < mesh->nNumIndices; i++)
		mesh->vIndexes[i] = arr[i];

	mesh->vColors.reserve(mesh->mNumVertices);
	for (int i = 0; i < mesh->mNumVertices; i++)
		mesh->vColors.emplace_back(0, 1, 0, 1);

	int verticesPorCara = 3;
	mesh->vCaras.resize(mesh->nNumIndices / verticesPorCara);
	for (int i = 0; i < mesh->nNumIndices / verticesPorCara; i++)
	{
		mesh->vCaras[i] = Cara(mesh->vIndexes[i * verticesPorCara],
							   mesh->vIndexes[i * verticesPorCara + 1],
							   mesh->vIndexes[i * verticesPorCara + 2]);
	}

	mesh->buildNormalVectors();

	return mesh;
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
	vNormals.resize(mNumVertices);

	std::vector<glm::dvec3> vAuxNormals = vNormals; // vector auxiliar

	for (int i = 0; i < nNumIndices / 3; i++)
	{
		glm::dvec3 v0 = vVertices[vIndexes[i * 3]];
		glm::dvec3 v1 = vVertices[vIndexes[i * 3 + 1]];
		glm::dvec3 v2 = vVertices[vIndexes[i * 3 + 2]];

		glm::dvec3 v = v1 - v0;
		glm::dvec3 w = v2 - v0;

		const glm::dvec3 n = normalize(cross(v, w));


		vAuxNormals[vIndexes[i * 3]] += n;
		vAuxNormals[vIndexes[i * 3 + 1]] += n;
		vAuxNormals[vIndexes[i * 3 + 2]] += n;
	}

	for (int i = 0; i < mNumVertices; i++)
		vNormals[i] = normalize(vAuxNormals[i]);
}

MbR::MbR(GLint mm, GLint mn, glm::dvec3* perfil) :
	m(mm),
	n(mn),
	perfil(perfil)
{
	
}

MbR::~MbR()
{
	delete perfil;
	perfil = nullptr;
}

MbR* MbR::generateIndexMbR(GLint mm, GLint mn, glm::dvec3* perfil)
{
	MbR* mesh = new MbR(mm, mn, perfil);
	// Definir la primitiva como GL_TRIANGLES
	mesh->mPrimitive = GL_TRIANGLES;
	// Definir el número de vértices como nn*mm
	mesh->mNumVertices = (mn * mm);
	// Usar un vector auxiliar de vértices
	dvec3* vs = new glm::dvec3[mesh->mNumVertices];

	for (int i = 0; i < mn; i++)
	{
		// Generar la muestra i- ésima de vértices
		GLdouble theta = i * 360 / mn;
		theta /= 4;
		GLdouble c = cos(glm::radians(theta));
		GLdouble s = sin(glm::radians(theta));
		for (int j = 0; j < mm; j++)
		{
			GLdouble z = -s * perfil[j].x + c * perfil[j].z;
			GLdouble x = c * perfil[j].x + s * perfil[j].z; // anyadido
			int indice = i * mm + j;
			vs[indice] = glm::dvec3(x, perfil[j].y, z);
		}
	}

	for (int i = 0; i < mesh->mNumVertices; i++)
		mesh->vVertices.push_back(vs[i]);
	delete[] vs;

	int indiceMayor = 0;
	mesh->nNumIndices = mesh->mNumVertices * 6;
	mesh->vIndexes = new GLuint[mesh->nNumIndices];
	for (int i = 0; i < mesh->mNumVertices * 6; i++)
		mesh->vIndexes[i] = 0;

	// El contador i recorre las muestras alrededor del eje Y
	for (int i = 0; i < mn; i++)
	{
		// El contador j recorre los vértices del perfil ,
		// de abajo arriba . Las caras cuadrangulares resultan
		// al unir la muestra i- ésima con la (i +1)% nn - ésima
		for (int j = 0; j < mm - 1; j++)
		{
			// El contador indice sirve para llevar cuenta
			// de los índices generados hasta ahora . Se recorre
			// la cara desde la esquina inferior izquierda
			const int indice = i * mm + j;

			mesh->vIndexes[indiceMayor] = indice;
			indiceMayor++;
			mesh->vIndexes[indiceMayor] = (indice + mm) % (mn * mm);
			indiceMayor++;
			mesh->vIndexes[indiceMayor] = (indice + mm + 1) % (mn * mm);
			indiceMayor++;

			// Y análogamente se añaden los otros tres índices
			mesh->vIndexes[indiceMayor] = (indice + mm + 1) % (mn * mm);
			indiceMayor++;
			mesh->vIndexes[indiceMayor] = (indice + 1);
			indiceMayor++;
			mesh->vIndexes[indiceMayor] = indice;
			indiceMayor++;
		}
	}

	mesh->vNormals.reserve(mesh->mNumVertices);
	mesh->buildNormalVectors();

	return mesh;
}
