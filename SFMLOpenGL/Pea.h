#ifndef PEA_H
#define PEA_H
#include <SFML/Graphics.hpp>
#include "tinyc2.h"
#include <iostream>

/// <summary>
/// Simple class that draws a circle shape and uses tinyc2 for collision checking
/// </summary>

class Pea
{
public:
	Pea() = delete; // do not use default constructor
	Pea(float radius, sf::RenderWindow& t_window);

	void placePea(sf::Vector2f t_mousePos);
	void updatePea();
	inline bool getInUse() const { return m_inUse; };
	inline c2Circle getHitbox() const { return m_hitbox; };
	inline sf::CircleShape getBody() const { return m_body; };
	void setInUse(bool t_inUse) { m_inUse = t_inUse; };
	void render();

private:
	sf::CircleShape m_body;
	c2Circle m_hitbox;
	bool m_inUse{ false };
	const float c_STARTING_RADIUS;
	sf::RenderWindow& m_window;
};

#endif