#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 4.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
}

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
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

//Accessors
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

//Modifiers
void Player::setPos(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos.x,pos.y);
}

//Functions
void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if(this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::update()
{
	this->updateAttack();
}

void Player::updateAttack()
{
	if(this->attackCooldownMax > this->attackCooldown)
	    this->attackCooldown += 0.5f;
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

//Destructor
Player::~Player()
{

}
