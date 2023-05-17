#include "PowerUp.h"

//Private Functions
void PowerUp::initVariables()
{
	int index = rand() % 3;

	if (index == powerup::health) {
		this->type = powerup::health;
		this->texture.loadFromFile("Textures/health.png");
	}
	else if (index == powerup::power) {
		this->type = powerup::power;
		this->texture.loadFromFile("Textures/power.png");
	}
	else {
		this->type = powerup::shield;
		this->texture.loadFromFile("Textures/shield.png");
	}
}

void PowerUp::initSprite()
{
	this->sprite.setTexture(this->texture);
}

//Constructor
PowerUp::PowerUp(float posX, float posY)
{
	this->initVariables();
	this->initSprite();
	this->sprite.setPosition(sf::Vector2f(posX, posY));
}

//Accessors
const sf::FloatRect PowerUp::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f PowerUp::getPos() const
{
	return this->sprite.getPosition();
}

//Functions
void PowerUp::update()
{
	this->sprite.move(0.f, this->speed);
}

void PowerUp::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

//Destructor
PowerUp::~PowerUp()
{

}
