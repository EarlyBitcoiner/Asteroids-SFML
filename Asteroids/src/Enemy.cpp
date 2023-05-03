
#include "Enemy.h"

//Private Functions
void Enemy::initVariables()
{
	this->speed = 2.5f;
	this->type = 0;
	this->hp = 0;
	this->hpMax = 10;
	this->damage = 1;
	this->points = 5;
}

void Enemy::initShape()
{
	this->shape.setRadius(rand() % 20 + 20);
	this->shape.setPointCount(rand() % 10 + 3);
	this->shape.setFillColor(sf::Color(rand() % 254 + 1, rand() % 254 + 1, 255));
}

//Constructor
Enemy::Enemy(float posX, float posY)
{
	this->initShape();
	this->shape.setPosition(posX,posY);
	this->initVariables();
}

//Accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

//Functions
void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

//Destructor
Enemy::~Enemy()
{

}
