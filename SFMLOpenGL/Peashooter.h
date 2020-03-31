#ifndef PEASHOOTER_H
#define PEASHOOTER_H

/// <summary>
/// Peashooter class that emulates a pool pattern by using a vector of Pea classes.
/// </summary>

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Pea.h"

class Peashooter
{
public:
	Peashooter() = delete; // do not use the default constructor
	Peashooter(int t_numOfPeas, float t_peaSize, sf::RenderWindow& t_window);
	~Peashooter();
private:
	std::vector<Pea> m_peas;

	sf::Sound m_popSound;
	sf::SoundBuffer m_popBuffer;

public:
	void shootPea(sf::Vector2f t_mousePos);
	void updatePeas();
	inline bool isPeaActive(int t_numOfPea) const { return m_peas[t_numOfPea].getInUse(); };
	c2Circle getPeaHitbox(int t_numOfPea) const { return m_peas[t_numOfPea].getHitbox(); };
	void setPeaActive(bool t_active, int t_numOfPea) { m_peas[t_numOfPea].setInUse(t_active); };
	void drawPeas();
	
};

#endif