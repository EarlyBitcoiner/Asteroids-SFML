
#include "Enemy.h"

//Private Functions
void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3; // min = 3 max = 10
	this->speed = (this->pointCount > 6) ? (rand() % 3) / 2 : this->pointCount / 2;
	this->type = 0;
	this->hpMax = this->pointCount;
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
}

void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount * 9);
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

//Modifiers
void Enemy::setHp(int hp)
{
	this->hp = hp;
}

void Enemy::loseHp(int hp)
{
	this->hp -= hp;
	if (this->hp < 0)
		this->hp = 0;
}

//Accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const sf::Vector2f Enemy::getPos() const
{
	return this->shape.getPosition();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

const int& Enemy::getHp() const
{
	return this->hp;
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
