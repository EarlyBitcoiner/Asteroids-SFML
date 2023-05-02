#include "Bullet.h"

//Constructor
Bullet::Bullet(sf::Texture* texture,float posX,float posY, float dirX, float dirY, float movementSpeed)
{
	this->shape.setTexture(*texture);

	this->shape.setPosition(posX,posY);
	this->direction.x = dirX;
	this->direction.y = dirY;
	this->movementSpeed = movementSpeed;
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

//Functions
void Bullet::update()
{
	//Movement
	this->shape.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

//Destructor
Bullet::~Bullet()
{
	delete texture;
}
