#ifndef GAME_H
#define GAME_H

#include <string>
#include <sstream>

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <fstream>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <Debug.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <GameObject.h>
#include "Peashooter.h"

using namespace std;
using namespace sf;
using namespace glm;

class Game
{
public:
	Game();
	Game(sf::ContextSettings settings);
	~Game();
	void run();
private:
	GameObject* game_object[2];
	RenderWindow window;
	Clock clock;
	Time time;
	bool animate = false;
	vec3 animation = vec3(0.0f);
	float rotation = 0.0f;
	bool isRunning = false;
	void initialize();
	void initCubes();
	void update();
	void render();
	void drawCube(const mat4& t_mvp);
	void unload();
	std::string readShader(std::string t_fileName);

	sf::Texture backgroundTex;
	sf::Sprite bgSprite;

	sf::Music m_bgm;

	int score{ 0 };

	Peashooter m_peashooter;
};

#endif  // ! GAME_H