#include "Explosion.h"

//Private Functions
void Explosion::initVariables()
{
	this->lifeTimeOver = false;
	this->lifeTimeMax = 150.f;
	this->lifeTime = 0.f;
}

//Constructor
Explosion::Explosion(sf::Texture& tex,const sf::Vector2f& pos)
{
	this->sprite.setTexture(tex);
	this->sprite.setPosition(pos);

	float scaleX = 1 / (this->sprite.getGlobalBounds().width / 120);
	float scaleY = 1 / (this->sprite.getGlobalBounds().height / 120);

	//this->sprite.setScale(0.09f, 0.09f);
	this->sprite.setScale(scaleX, scaleY);

	this->initVariables();
}

//Functions
void Explosion::update()
{
	if (lifeTime < lifeTimeMax)
	{
		lifeTime += 1.f;
	}
	else
	{
		this->lifeTimeOver = true;
	}
}

void Explosion::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

const bool Explosion::getLifeTimeOver() const
{
	return this->lifeTimeOver;
}

//Destructor
Explosion::~Explosion()
{

}
