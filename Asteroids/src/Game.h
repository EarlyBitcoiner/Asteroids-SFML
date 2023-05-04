#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <sstream>
#include <map>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class Game {
private:
	//Window
	sf::RenderWindow* window;

	//Systems
	unsigned points;
	
	//Player
	Player* player;

	//Player GUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	sf::Text gameOverText;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//GUI
	sf::Font font;
	sf::Text pointText;

	//World
	sf::Sprite worldBackground;
	sf::Texture worldBackgroundTex;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//Private Functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initPlayer();
	void initEnemies();
public:
	Game();

	//Functions
	void run();

	void updatePollEvents();

	void updateInput();

	void updateGUI();

	void updateWorld();

	void updateCollision();

	void updateBullets();

	void updateEnemies();

	void updateCombat();

	void update();

	void renderGUI();

	void renderWorld();

	void render();

	//Destructor
	virtual ~Game();
};

#endif
