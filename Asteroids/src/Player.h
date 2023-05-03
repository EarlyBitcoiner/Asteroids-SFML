#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdexcept>

class Player {
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	//Private Functions
	void initVariables();
	void initTexture();
	void initSprite();
public:
	Player();

	//Accessor
	const sf::Vector2f& getPos() const;

	const sf::FloatRect getBounds() const;

	//Modifiers
	void setPos(const sf::Vector2f pos);

	//Function
	void move(const float dirX, const float dirY);

	const bool canAttack();

	void update();

	void updateAttack();

	void render(sf::RenderTarget& target);

	//Destructor
	virtual ~Player();
};