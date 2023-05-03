#ifndef GAME_H
#define GAME_H

#include <map>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class Game {
private:
	//Window
	sf::RenderWindow* window;
	
	//Player
	Player* player;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//Private Functions
	void initWindow();
	void initTextures();
	void initPlayer();
	void initEnemies();
public:
	Game();

	//Functions
	void run();

	void updatePollEvents();

	void updateInput();

	void updateBullets();

	void updateEnemies();

	void update();

	void render();

	//Destructor
	virtual ~Game();
};

#endif
