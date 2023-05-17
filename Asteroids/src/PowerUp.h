#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdexcept>

enum powerup{ health = 0,
	power,
	shield
};

class PowerUp {
private:

	sf::Sprite sprite;
	sf::Texture texture;

	float speed = 5.f;
	powerup type;

	//Private Functions
	void initVariables();
	void initSprite();
public:
	//Constructor
	PowerUp(float posX, float poxY);

	//Accessors
	const sf::FloatRect getBounds() const;

	const sf::Vector2f getPos() const;

	//Functions
	void update();

	void render(sf::RenderTarget& target);

	//Destructor
	virtual ~PowerUp();
};

#endif
