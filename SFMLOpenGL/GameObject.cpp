#include "GameObject.h"

GameObject::GameObject() : model(1.0f)
{
}

/// <summary>
/// Setup, or re-setup this Game Object.
/// </summary>
/// <param name="t_position">Where the Game Object begins</param>
/// <param name="t_model">The Model's starting Matrix</param>
void GameObject::initialize(const mat4& t_model)
{
	// I convert the mat4 into a float pointer to access it's data
	// there is no direct way i could find 
	const float* modelData = (const float*)glm::value_ptr(t_model);

	// each 1 unit in the translation part of the matrix is roughly 56 pixels
	// using this knowledge, i can rougly guess where the cube is in terms of Vector2f
	// 400 is added as 0 on x is in the center of the screen -- aka at 400
	position = sf::Vector2f{ (modelData[12] * 56.0f) + s_SCREEN_WIDTH / 2, modelData[13] };

	model = t_model;
	speed = ((rand() % 10) + 3) / 100.0f; // get a random speed from 0.03 to 0.1
}

/// <summary>
/// Update GameObject properties
/// </summary>
void GameObject::update()
{
	updateModel(translate(model, glm::vec3(-speed, 0.0f, 0.0)));
	updatePosition(sf::Vector2f{ -speed, 0.0f });
	pathEndCheck();
}

/// <summary>
/// Update position of Game Object relative to screen
/// </summary>
/// <param name="t_direction">The direction the GameObject wants to move</param>
void GameObject::updatePosition(sf::Vector2f t_direction)
{
	position.x += t_direction.x * 56;
	// since each 1 unit is roughly equal to 56 pixels,
	// i multiply the direction the cube wants to move by 56.
	// this means if the cube wants to move by 0.1, it'll move by 5.6 pixels
}

/// <summary>
/// Check to see if the GameObject has gone off-screen
/// </summary>
void GameObject::pathEndCheck()
{
	// check if the GameObject is off the screen by 1/4th the amount of the width
	if (position.x < -s_SCREEN_WIDTH / 4.0f)
	{ // check to see if the cube has gone off screen
		initialize(translate(mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f)));
		// if it has, reinitialize it
	}
}
