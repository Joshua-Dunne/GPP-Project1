#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <GL/glew.h>
#include <GL/wglew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class GameObject
{
public:
	GameObject();
	// Constructors
	// Gets and Sets
	// Checking Collisions
	// mat4 for the model

private:
	// Vertex
	// Colors
	// UV's
	// model
	// collider tinyc2

	mat4 model;

public:
	const mat4 getModel() { return model; };
	void updateModel(mat4& t_newModel) { model = t_newModel; };
};

#endif