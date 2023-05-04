#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdexcept>

class Bullet {
private:
	sf::Sprite shape;
	sf::Texture* texture;

	sf::Vector2f direction;

	float movementSpeed;
	float damage;

public:
	//Constructors
	Bullet() = default;

	Bullet(sf::Texture* texture,float posX,float posY, float dirX, float dirY, float movementSpeed, float damage);

	const sf::FloatRect getBounds() const;

	//Accessors
	const float getDamage() const;

	//Functions
	void update();

	void render(sf::RenderTarget& target);

	//Destructor
	virtual ~Bullet();
};

#endif BULLET_H