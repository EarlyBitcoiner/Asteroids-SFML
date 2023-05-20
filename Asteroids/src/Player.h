#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdexcept>
#include <map>

#include "PowerUp.h"

class Player 
{
private:
	sf::Sprite sship;
	sf::Sprite shield;
	sf::Texture sshipTex;
	sf::Texture shieldTex;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	std::map<powerup, float> activePowerups;

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

	const bool powerActive() const;

	const bool shieldActive() const;

	//Modifiers
	void setPos(const sf::Vector2f pos);

	void setHp(const int hp);

	void loseHp(const int hp);
		
	//Function
	void move(const float dirX, const float dirY);

	const bool canAttack();

	void absorbPowerup(PowerUp* power);

	void update();

	void updateAttack();

	void updatePowerups();

	void updateShieldPos();

	void render(sf::RenderTarget& target);

	//Destructor
	virtual ~Player();
};

#endif PLAYER_H