#include "GameObject.h"
#include "tinyc2.h"

GameObject::GameObject() : 
	model(1.0f), 
	m_screenWidth(800.0f), 
	m_screenHeight(600.0f), 
	m_cameraZDistance(10.0f)
{
}

GameObject::GameObject(float t_screenWidth, float t_screenHeight, float t_cameraZDistance):
	model(1.0f),
	m_screenWidth(t_screenWidth),
	m_screenHeight(t_screenHeight),
	m_cameraZDistance(t_cameraZDistance)
{

}

/// <summary>
/// Setup, or re-setup this Game Object.
/// </summary>
/// <param name="t_position">Where the Game Object begins</param>
/// <param name="t_model">The Model's starting Matrix</param>
void GameObject::initialize(const glm::mat4& t_model)
{
	// I convert the mat4 into a float pointer to access it's data
	// there is no direct way i could find 
	const float* modelData = (const float*)glm::value_ptr(t_model);

	model = t_model;
	speed = ((rand() % 10) + 3) / 100.0f; // get a random speed from 0.03 to 0.1

	position.y = m_screenHeight * ( ((modelData[13] / (4.0f/3.0f) ) + m_cameraZDistance) / (10.0f * 2));
	// only need to calculate position once, since the position for collisions will never change on Y
	// aka the cube will never rise/fall from it's position, so we don't need to account for it
	// but we do need to know what the initial y position of the cube is for later collision checking
	// 4/3 is the aspect ratio
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
	const float* modelData = (const float*)glm::value_ptr(model);
	position.x = m_screenWidth * ((modelData[12] + m_cameraZDistance) / (m_cameraZDistance * 2));
	
}

/// <summary>
/// Check to see if the GameObject has gone off-screen
/// </summary>
void GameObject::pathEndCheck()
{
	// check if the GameObject is off the screen by 1/4th the amount of the width
	if (position.x < -0)
	{ // check to see if the cube has gone off screen
		initialize(translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f)));
		// if it has, reinitialize it
	}
}

void GameObject::collisionCheck(sf::Vector2f t_mousePosition)
{
	c2Circle mouseCircle;
	mouseCircle.p = c2V(t_mousePosition.x, t_mousePosition.y);
	mouseCircle.r = 20.0f;

	float cubeSize = ((2.0f / (m_cameraZDistance - 1.0f))) * (m_screenWidth / 2.0f);
	// we do -1 to the cameraZDistance to get the face closer to the camera for collision checking

	c2Circle cubeCircle;
	cubeCircle.p = c2V(position.x, position.y);
	cubeCircle.r = glm::length(glm::vec2(cubeSize, cubeSize)) / 2.0f;

	if (c2CircletoCircle(mouseCircle, cubeCircle)) // 1 - true, 0 - false
	{
		initialize(translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f)));
	}
	
}
