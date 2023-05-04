
#include "Enemy.h"

//Private Functions
void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3; // min = 3 max = 10
	this->speed = this->pointCount / 3;
	this->type = 0;
	this->hpMax = this->pointCount;
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
}

void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount * 10);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 254 + 1, rand() % 254 + 1, 255));
}

//Constructor
Enemy::Enemy(float posX, float posY)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(posX,posY);
}

//Accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
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
