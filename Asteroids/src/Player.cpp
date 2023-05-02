#include "Player.h"

void Player::initTexture()
{
   // Load a texture from file.
	this->texture.loadFromFile("C:/Users/user/source/repos/Asteroids/Asteroids/src/Textures/ship.png");
}

void Player::initSprite()
{
  // Set texture to a sprite.
	this->sprite.setTexture(this->texture);

  // Resize the sprite.
	this->sprite.scale(0.1f,0.1f);
}

//Constructor
Player::Player()
{
	this->movementSpeed = 3.f;

	this->initTexture();
	this->initSprite();
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

//Functions
void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::update()
{

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

//Destructor
Player::~Player()
{

}
