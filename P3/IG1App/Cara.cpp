#include "Cara.h"

Cara::Cara(glm::dvec3 v0, glm::dvec3 v1, glm::dvec3 v2)
{
	numVertices = 3;

	vVertices.resize(3);
	vVertices[0] = v0;
	vVertices[1] = v1;
	vVertices[2] = v2;
}

Cara::Cara(int v0, int v1, int v2)
{
	numVertices = 3;

	vIndices.resize(3);
	vIndices[0] = v0;
	vIndices[1] = v1;
	vIndices[2] = v2;
}

int Cara::getIndice(int i)
{
	return vIndices[i];
}
