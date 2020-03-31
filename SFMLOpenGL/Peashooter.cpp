#include "Peashooter.h"

Peashooter::Peashooter(int t_numOfPeas, float t_peaSize, sf::RenderWindow& t_window)
{
	for (int i = 0; i < t_numOfPeas; ++i)
	{
		m_peas.reserve(t_numOfPeas); 
		// make room for any peas we have to make before hand
		m_peas.push_back(Pea(t_peaSize, t_window));
	}
}

Peashooter::~Peashooter()
{
}

/// <summary>
/// Place the next available Pea at the mouse cursor
/// </summary>
/// <param name="t_mousePos"></param>
void Peashooter::shootPea(sf::Vector2f t_mousePos)
{
	for (auto& currentPea : m_peas)
	{
		if (!currentPea.getInUse())
		{
			currentPea.placePea(t_mousePos); // place the Pea
			break; // break out of the loop since we found the next available Pea
		}
	}
}

void Peashooter::updatePeas()
{
	for (auto& currentPea : m_peas)
	{
		currentPea.updatePea(); // update any peas
	}
}

void Peashooter::drawPeas()
{
	for (auto& currentPea : m_peas)
	{
		if (currentPea.getInUse())
		{
			currentPea.render();
		}
	}
}