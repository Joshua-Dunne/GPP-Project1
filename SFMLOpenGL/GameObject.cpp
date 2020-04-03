#include "GameObject.h"

GameObject::GameObject() : 
	m_model(1.0f),
	m_screenWidth(800.0f), 
	m_screenHeight(600.0f), 
	m_cameraZDistance(10.0f),
	m_health(0)
{
	if (!m_hitBuffer.loadFromFile("./Assets/Sounds/cubeHit.ogg"))
	{
		std::cerr << "error loading cubeHit.ogg" << std::endl;
	}

	m_hitSound.setBuffer(m_hitBuffer);
}
	
GameObject::GameObject(float t_screenWidth, float t_screenHeight, float t_cameraZDistance):
	m_model(1.0f),
	m_screenWidth(t_screenWidth),
	m_screenHeight(t_screenHeight),
	m_cameraZDistance(t_cameraZDistance),
	m_health(0)
{
	if (!m_hitBuffer.loadFromFile("./Assets/Sounds/cubeHit.ogg"))
	{
		std::cerr << "error loading cubeHit.ogg" << std::endl;
	}

	m_hitSound.setBuffer(m_hitBuffer);
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

	m_model = t_model;
	m_speed = ((rand() % 10) + 3) / 1000.0f; // get a random speed from 0.003 to 0.01

	m_position.y = m_screenHeight * ( ((modelData[13] / (4.0f/3.0f) ) + m_cameraZDistance) / (10.0f * 2));
	// only need to calculate position once, since the position for collisions will never change on Y
	// aka the cube will never rise/fall from it's position, so we don't need to account for it
	// but we do need to know what the initial y position of the cube is for later collision checking
	// 4/3 is the aspect ratio

	m_health = (rand() % 3) + 1; // set random health value each init
}

/// <summary>
/// Update GameObject properties
/// </summary>
void GameObject::update()
{
	if (finishedFalling)
	{
		updateModel(translate(m_model, glm::vec3(-m_speed, 0.0f, 0.0)));
		// translate the model itself based on the speed
		updatePosition();
		// find the new position where the cube is now
		pathEndCheck();
		// check to see if the GameObject has reached the end of it's path
	}
	else
	{
		playHitAnimation();
		// play an animation if the cube is hit
	}
}

/// <summary>
/// Update position of Game Object relative to screen
/// </summary>
void GameObject::updatePosition()
{
	const float* modelData = (const float*)glm::value_ptr(m_model);
	// get the model data from the mat4
	m_position.x = m_screenWidth * ((modelData[12] + m_cameraZDistance) / (m_cameraZDistance * 2));
	// get the x position based on the camera
	m_position.y = m_screenHeight * (((modelData[13] / (4.0f / 3.0f)) + m_cameraZDistance) / (10.0f * 2));
	// get the y position based on the camera
}

/// <summary>
/// Check to see if the GameObject has gone off-screen
/// </summary>
void GameObject::pathEndCheck()
{
	// check if the GameObject is off the screen
	if (m_position.x < 0)
	{ // if it has, reinitialize it
		initialize(translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f)));
	}
}

/// <summary>
/// Check for collisions against Pea hitboxes
/// </summary>
/// <param name="t_peaHitbox">tinyc2 hitbox of Pea</param>
void GameObject::collisionCheck(c2Circle t_peaHitbox)
{
	// Only do collision checks for this game object
	// If the cube is not already hit by the player
	if (!m_isHit)
	{
		float cubeSize = ((2.0f / (m_cameraZDistance - 1.0f))) * (m_screenWidth / 2.0f);
		// we do -1 to the cameraZDistance to get the face closer to the camera for collision checking

		c2Circle cubeCircle;
		cubeCircle.p = c2V(m_position.x, m_position.y);
		cubeCircle.r = glm::length(glm::vec2(cubeSize, cubeSize)) / 2.0f;
		// divide by 2 to get the radius of the diameter

		if (c2CircletoCircle(t_peaHitbox, cubeCircle)) // 1 - true, 0 - false
		{
			
			m_hitSound.play();
			m_isHit = true;
			m_health--; // take away health now that cube is hit
			
			if (m_health <= 0) // if the cube is out of health, play falling animations
			{
				finishedFalling = false;
				m_acceleration = m_speed * 10.0f;
			}
		}
	}
}

/// <summary>
/// Play a short animation to show the player the cube was hit
/// </summary>
void GameObject::playHitAnimation()
{
	updateModel(translate(m_model, glm::vec3(0.0f, m_acceleration, m_speed)));
	// translate the model based on speed and acceleration
	updatePosition();
	// find the position of the model afterwards

	if (m_position.y < 0.0f)
	{ // if the GameObject has fallen off-screen
		initialize(translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f)));
		// put it back to it's starting position
		finishedFalling = true;
		// this GameObject is no longer hit
	}

	m_acceleration -= m_speed * 0.075f; // gradually make the cube falls down
}
