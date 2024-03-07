#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include <vector>

constexpr int NUM_TEXTURES = 5;

class Scene
{
public:
	Scene() = default;
	~Scene()
	{
		freeObjects();
		freeTextures();
		resetGL();
	};

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	void init();

	void render(Camera const& cam) const;
	void update();

	void setScene(GLint id);

protected:
	const std::string textureRoot = "../bmps/";

	const std::string imgs[NUM_TEXTURES]{
		std::string {"windowV.bmp"},
		std::string {"baldosaC.bmp"},
		std::string {"container.bmp"},
		std::string {"papelE.bmp"},
		std::string {"baldosaP.bmp"}
	};

	enum TextureName
	{
		FOTO,
		VENTANA,
		BALDOSA,
		CAJA_A,
		CAJA_B,
		ESTRELLA
	};

	GLint mId = 0;

	void freeObjects();
	void freeTextures();
	void setGL();
	void resetGL();
	void loadTextures();

	std::vector<Texture*> gTextures;
	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
};

#endif //_H_Scene_H_
