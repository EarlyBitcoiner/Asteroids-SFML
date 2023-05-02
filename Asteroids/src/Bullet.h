#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdexcept>

class Bullet {
private:
	sf::Sprite shape;
	sf::Texture* texture;

	sf::Vector2f direction;
	float movementSpeed;

public:
	//Constructors
	Bullet() = default;

	Bullet(sf::Texture* texture,float posX,float poxY, float dirX, float dirY, float movementSpeed);

	const sf::FloatRect getBounds() const;

	//Functions
	void update();

	void render(sf::RenderTarget& target);

	//Destructor
	virtual ~Bullet();
};
