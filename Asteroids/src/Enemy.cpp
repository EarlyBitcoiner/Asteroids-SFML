
#include "Enemy.h"

//Private Functions
void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3; // min = 3 max = 10
	this->speed = (this->pointCount > 6) ? (rand() % 3) / 2 : this->pointCount / 2;
	this->type = 0;
	this->hpMax = this->pointCount * 1.5;
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount * 3;
}

void Enemy::initSprite()
{
	this->texture.loadFromFile("Textures/asteroid1.png");

	this->sprite.setTexture(this->texture);

	if(this->pointCount == 3)
	{
		this->sprite.setScale(0.1f, 0.1f);
	}
	else if(this->pointCount <=5)
	{
		this->sprite.setScale(0.15f, 0.15f);

	}
	else if (this->pointCount == 6)
	{
		this->sprite.setScale(0.2f, 0.2f);
	}
	else if(this->pointCount <=9)
	{
		this->sprite.setScale(0.25f,0.25f);
	}
	else
	{
		this->sprite.setScale(0.3f, 0.3f);
	}
}

//Constructor
Enemy::Enemy(float posX, float posY)
{
	this->initVariables();
	this->initSprite();
	this->sprite.setPosition(posX,posY);
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
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Enemy::getPos() const
{
	return this->sprite.getPosition();
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
	this->sprite.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

//Destructor
Enemy::~Enemy()
{

}
