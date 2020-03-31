#include "Peashooter.h"

Peashooter::Peashooter(int t_numOfPeas, float t_peaSize, sf::RenderWindow& t_window)
{
	for (int i = 0; i < t_numOfPeas; ++i)
	{
		m_peas.reserve(t_numOfPeas); 
		// make room for any peas we have to make before hand
		m_peas.push_back(Pea(t_peaSize, t_window));
	}

	if (!m_popBuffer.loadFromFile("./Assets/Sounds/peaShoot.ogg"))
	{
		std::cerr << "error loading peashoot.ogg" << std::endl;
	}

	m_popSound.setBuffer(m_popBuffer);
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
		{ // if this pea isn't in use
			currentPea.placePea(t_mousePos); // place the Pea
			m_popSound.play();
			break; // break out of the loop since we found the next available Pea
		}
	}
}

/// <summary>
/// Update any peas that are ready to be updated
/// </summary>
void Peashooter::updatePeas()
{
	for (auto& currentPea : m_peas)
	{
		currentPea.updatePea(); // update any peas
	}
}

/// <summary>
/// Draw any peas that are ready to be drawn
/// </summary>
void Peashooter::drawPeas()
{
	for (auto& currentPea : m_peas)
	{
		if (currentPea.getInUse())
		{ // if this pea is being used
			currentPea.render();
			// render it
		}
	}
}
