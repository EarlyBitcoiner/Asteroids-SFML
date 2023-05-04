#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdexcept>

class Player 
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	int hp;
	int hpMax;

	//Private Functions
	void initVariables();
	void initTexture();
	void initSprite(sf::RenderTarget& target);
public:
	Player(sf::RenderTarget& target);

	//Accessor
	const sf::Vector2f& getPos() const;

	const sf::FloatRect getBounds() const;

	const int& getHp() const;
	const int& getHpMax() const;

	//Modifiers
	void setPos(const sf::Vector2f pos);

	void setHp(const int hp);

	void loseHp(const int hp);

	//Function
	void move(const float dirX, const float dirY);

	const bool canAttack();

	void update();

	void updateAttack();

	void render(sf::RenderTarget& target);

	//Destructor
	virtual ~Player();
};