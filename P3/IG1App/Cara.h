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

	int getIndiceVertice(glm::dvec3 vec) const
	{
		const auto it
			= std::ranges::find(vVertices.begin(),
				vVertices.end(),
				vec);

		int index = -1;
		if (it != vVertices.end())
			index = it - vVertices.begin();

		return index;
	}

	int getIndiceVertice(glm::dvec3 vertex, std::vector<glm::dvec3> vector) const
	{
		const auto it
			= std::ranges::find(vector.begin(),
				vector.end(),
				vertex);

		int index = -1;
		if (it != vector.end())
			index = it - vector.begin();

		return index;
	}

	glm::dvec3 getVerticeIndice(int index) const
	{
		return vVertices[index];
	}
};

