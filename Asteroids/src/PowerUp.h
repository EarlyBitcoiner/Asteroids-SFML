#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdexcept>

enum powerup{ health = 0,
	power = 1,
	shield = 2
};

class PowerUp {
private:

	sf::Sprite sprite;
	sf::Texture texture;

	float speed = 1.5f;
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

	const powerup getType() const;

	//Functions
	void update();

	void render(sf::RenderTarget& target);

	//Destructor
	virtual ~PowerUp();
};

#endif
