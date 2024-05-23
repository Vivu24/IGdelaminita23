#pragma once
#include <vector>
#include <glm/vec3.hpp>
class Cara
{
public:
	Cara() = default;
	Cara(glm::dvec3 v0, glm::dvec3 v1, glm::dvec3 v2);
	Cara(int v0, int v1, int v2);
	~Cara() = default;

	int numVertices;
	std::vector<glm::dvec3> vVertices;
	std::vector<int> vIndices;

	int getIndice(int i);
};

