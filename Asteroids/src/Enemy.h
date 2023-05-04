#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdexcept>

class Enemy
{
private:
	unsigned pointCount;

	sf::CircleShape shape;

	float speed;
	int type;
	int hp;
	int hpMax;
	int damage;
	int points;

	//Private Functions
	void initVariables();
	void initShape();
public:
	//Constructor
	Enemy(float posX, float posY);

	//Accessors
	const sf::FloatRect getBounds() const;

	const int& getPoints() const;

	const int& getDamage() const;

	//Functions
	void update();

	void render(sf::RenderTarget& target);

	//Destructor
	virtual ~Enemy();
};

#endif