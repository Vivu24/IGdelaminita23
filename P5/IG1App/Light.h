#pragma once

#include <GL/freeglut.h>
#include <glm/glm.hpp>

class Light { // Abstract class
protected:
	static GLuint cont; // Atributo para poder generar un nuevo id cada vez
	GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS; // Primer id no válido
	// Atributos lumínicos y geométrico de la fuente de luz
	glm::fvec4 ambient = { 0.1 , 0.1 , 0.1 , 1 };
	glm::fvec4 diffuse = { 0.5 , 0.5 , 0.5 , 1 };
	glm::fvec4 specular = { 0.5 , 0.5 , 0.5 , 1 };
	glm::fvec4 posDir = { 0 , 0 , 1 , 0 };
	// Añade setters para cambiar el valor de los atributos lumínicos
public:
	Light();
	virtual ~Light() { disable(); }
	void uploadL() const;
	// Método abstracto
	virtual void upload(glm::dmat4 const& modelViewMat) = 0;
	void disable();
	void enable();
	void setAmb(glm::fvec4 amb);
	void setDiff(glm::fvec4 diff);
	void setSpec(glm::fvec4 spec);
	void setID(GLuint newID) { id = newID; }
};


class DirLight : public Light {
public:
	virtual void upload(glm::dmat4 const& modelViewMat) override;
	void setPosDir(glm::fvec3 dir);
};

class PosLight : public Light {
protected:
	// Factores de atenuación
	GLfloat kc_ = 1, kl_ = 0, kq_ = 0;
public:
	virtual void upload(glm::dmat4 const& modelViewMat) override;
	void setPosDir(glm::fvec3 dir);
	void setAtte(GLfloat kc, GLfloat kl, GLfloat kq);
};

class SpotLight : public PosLight {
protected:
	// Atributos del foco
	glm::fvec4 direction = { 0 , 0 , -1 , 0 };
	GLfloat cutoff = 180;
	GLfloat exp = 0;
public:
	SpotLight(glm::fvec3 pos = { 0 , 0 , 0 }) : PosLight() {
		posDir = glm::fvec4(pos, 1.0);
	};
	virtual void upload(glm::dmat4 const& modelViewMat) override;
	void setSpot(glm::fvec3 dir, GLfloat cf, GLfloat e);
};


