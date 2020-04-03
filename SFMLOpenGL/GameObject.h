#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <GL/glew.h>
#include <GL/wglew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "./ScreenSize.h"
#include "tinyc2.h"


class GameObject
{
public:
	GameObject();
	GameObject(float t_screenWidth, float t_screenHeight, float t_cameraZDistance);
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

	glm::mat4 m_model;
	sf::Vector2f m_position;
	
	float m_speed{ 0.0f }; // how fast this cube will move from right to left
	float m_acceleration{ 0.0f };
	float m_cameraZDistance; // how far away the camera is on the Z axis

	const float m_screenWidth;
	const float m_screenHeight;

	bool m_isHit{ false }; // whether or not this cube was hit
	bool finishedFalling{ false }; // whether or not this cube has finished its falling

	int m_health;

	sf::SoundBuffer m_hitBuffer;
	sf::Sound m_hitSound;
	
	
public:
	void initialize(const glm::mat4& t_model);
	inline const glm::mat4 getModel() const { return m_model; };
	inline const sf::Vector2f getPosition() const { return m_position; };
	inline const bool getHit() const { return m_isHit; };
	inline const bool doneFalling() const { return finishedFalling; };
	inline void setHit(bool t_wasHit) { m_isHit = t_wasHit; };
	void update();
	inline void updateModel(const glm::mat4& t_newModel) { m_model = t_newModel; };
	void updatePosition();
	void pathEndCheck();
	void collisionCheck(c2Circle t_peaHitbox);
	void playHitAnimation();
};

#endif