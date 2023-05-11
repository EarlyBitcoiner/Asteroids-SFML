#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdexcept>

class Enemy
{
private:
	unsigned pointCount;

	sf::Sprite sprite;
	sf::Texture texture;

	float speed;
	int type;
	int hp;
	int hpMax;
	int damage;
	int points;

	//Private Functions
	void initVariables();
	void initSprite();
public:
	//Constructor
	Enemy(float posX, float posY);

	//Modifiers

	void setHp(int hp);

	void loseHp(int hp);

	//Accessors
	const sf::FloatRect getBounds() const;

	const sf::Vector2f getPos() const;

	const int& getPoints() const;

	const int& getDamage() const;

	const int& getHp() const;

	//Functions
	void update();

	void render(sf::RenderTarget& target);

	//Destructor
	virtual ~Enemy();
};

#endif