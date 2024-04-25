#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include <vector>

constexpr int NUM_TEXTURES = 1;

class Scene
{
public:
	Scene() = default;
	~Scene()
	{
		freeTextures();
		freeObjects();
		resetGL();
	};

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	void init();

	void render(Camera const& cam) const;
	void update();

	void setScene(GLint id);

	void orbit(float time);
	void rotate(float time);

protected:
	const std::string textureRoot = "../bmps/";

	const std::string imgs[NUM_TEXTURES]{
		std::string {"noche.bmp"}
	};

	enum TextureName
	{
		NOCHE
	};

	GLint mId = 0;

	GLdouble rotY;

	void freeObjects();
	void freeTextures();
	void setGL();
	void resetGL();
	void loadTextures();

	// Lo dejo protected de momento
	void sceneDirLight(Camera const& cam) const;

	std::vector<Texture*> gTextures;
	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
};

#endif //_H_Scene_H_
