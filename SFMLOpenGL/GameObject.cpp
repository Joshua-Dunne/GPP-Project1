#include "GameObject.h"
#include "./tinyc2.h"

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
	speed = ((rand() % 10) + 3) / 1000.0f; // get a random speed from 0.003 to 0.01

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
	if (!isHit)
	{
		updateModel(translate(model, glm::vec3(-speed, 0.0f, 0.0)));
		updatePosition();
		pathEndCheck();
	}
	else
	{
		playHitAnimation();
	}
}

/// <summary>
/// Update position of Game Object relative to screen
/// </summary>
void GameObject::updatePosition()
{
	const float* modelData = (const float*)glm::value_ptr(model);
	position.x = m_screenWidth * ((modelData[12] + m_cameraZDistance) / (m_cameraZDistance * 2));
	position.y = m_screenHeight * (((modelData[13] / (4.0f / 3.0f)) + m_cameraZDistance) / (10.0f * 2));
}

/// <summary>
/// Check to see if the GameObject has gone off-screen
/// </summary>
void GameObject::pathEndCheck()
{
	// check if the GameObject is off the screen
	if (position.x < 0)
	{ // if it has, reinitialize it
		initialize(translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f)));
	}
}

void GameObject::collisionCheck(sf::Vector2f t_mousePosition)
{
	// Only do collision checks for this game object
	// If the cube is not already hit by the player
	if (!isHit)
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
			isHit = true;
		}
	}
}

/// <summary>
/// Play a short animation to show the player the cube was hit
/// </summary>
void GameObject::playHitAnimation()
{
	updateModel(translate(model, glm::vec3(0.0f, speed, 0.0f)));
	updatePosition();

	if (position.y > 600.0f)
	{
		initialize(translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f)));
		isHit = false;
	}
}
