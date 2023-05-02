#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdexcept>

class Player {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float movementSpeed;

	//Private Functions
	void initTexture();
	void initSprite();
public:
	Player();

	//Accessor
	const sf::Vector2f& getPos() const;

	//Function
	void move(const float dirX, const float dirY);

	void update();

	void render(sf::RenderTarget& target);

	//Destructor
	virtual ~Player();
};