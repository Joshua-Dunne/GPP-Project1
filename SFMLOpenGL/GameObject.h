#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <GL/glew.h>
#include <GL/wglew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML/System/Vector2.hpp>

#include <iostream>

#include "ScreenSize.h"

using namespace glm;
using namespace sf;

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
	Vector2f position;
	float speed{ 0.0f }; // how fast this cube will move from right to left

public:
	void initialize(const mat4& t_model);
	const mat4 getModel() const { return model; };
	const Vector2f getPosition() const { return position; };
	void update();
	inline void updateModel(mat4& t_newModel) { model = t_newModel; };
	void updatePosition(sf::Vector2f t_direction);
	void pathEndCheck();
};

#endif