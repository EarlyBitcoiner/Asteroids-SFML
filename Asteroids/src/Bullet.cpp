#include "Bullet.h"

//Constructor
Bullet::Bullet(sf::Texture* texture,float posX,float posY, float dirX, float dirY, float movementSpeed, float damage)
{
	this->shape.setTexture(*texture);
	this->shape.rotate(-90.f); 
	this->shape.setScale(sf::Vector2f(0.3f,0.3f));
	this->shape.setPosition(posX - Bullet::getBounds().width / 2, posY);

	this->direction.x = dirX;
	this->direction.y = dirY;
	this->movementSpeed = movementSpeed;
	this->damage = damage;
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const float Bullet::getDamage() const
{
	return this->damage;
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
