#include "Pea.h"

/// <summary>
/// Default constructor that sets a radius for the Pea and gets the window to draw it
/// </summary>
/// <param name="radius">Radius of Pea</param>
/// <param name="t_window">Window to draw to</param>
Pea::Pea(float radius, sf::RenderWindow& t_window) : c_STARTING_RADIUS{ 20.0f }, m_window(t_window)
{
	m_body.setRadius(radius);
	m_body.setOrigin(sf::Vector2f{ radius, radius }); // set origin to the center of circle shape
	m_body.setFillColor(sf::Color::Green);
}

/// <summary>
/// Place the Pea at the mouse position
/// </summary>
/// <param name="t_mousePos">Position of mouse (relative to window)</param>
void Pea::placePea(sf::Vector2f t_mousePos)
{
	m_body.setPosition(sf::Vector2f{ t_mousePos.x, -200.0f });
	// take the x position of the mouse, but ignore the mouse's y position
	m_body.setRadius(c_STARTING_RADIUS);

	m_hitbox.p = c2V(t_mousePos.x, t_mousePos.y);
	m_hitbox.r = c_STARTING_RADIUS;

	m_inUse = true;
}

/// <summary>
/// Update any peas that are in use
/// </summary>
void Pea::updatePea()
{
	if (m_inUse)
	{
		if (m_body.getPosition().y > 600 + m_body.getRadius() * 2)
		{
			// if the pea is off-screen, it is no longer in use
			m_inUse = false;
		}

		m_body.move(sf::Vector2f{ 0, 5.0f }); // move the pea's visual body
		m_hitbox.p = c2V(m_body.getPosition().x, m_body.getPosition().y); // move the pea's hitbox
	}
}

/// <summary>
/// Render any peas that are in use
/// </summary>
void Pea::render()
{
	if (m_inUse) // only draw if this pea is actually being used currently
		m_window.draw(m_body);
}
