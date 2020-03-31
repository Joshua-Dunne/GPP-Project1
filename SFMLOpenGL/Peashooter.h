#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Pea.h"

class Peashooter
{
public:
	Peashooter(int t_numOfPeas, float t_peaSize, sf::RenderWindow& t_window);
	~Peashooter();
private:
	std::vector<Pea> m_peas;

public:
	void shootPea(sf::Vector2f t_mousePos);
	void updatePeas();
	inline bool isPeaActive(int t_numOfPea) const { return m_peas[t_numOfPea].getInUse(); };
	c2Circle getPeaHitbox(int t_numOfPea) const { return m_peas[t_numOfPea].getHitbox(); };
	void setPeaActive(bool t_active, int t_numOfPea) { m_peas[t_numOfPea].setInUse(t_active); };
	void drawPeas();
	
};

#endif