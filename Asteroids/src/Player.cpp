#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 4.f;

	this->attackCooldownMax = 20.f;
	this->attackCooldown = this->attackCooldownMax;

	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Player::initTexture()
{
   // Load a texture from file.
	this->texture.loadFromFile("Textures/ship.png"); // C:/Users/user/source/repos/Asteroids/Asteroids/src/
}

void Player::initSprite(sf::RenderTarget& target)
{
  // Set texture to a sprite.
	this->sprite.setTexture(this->texture);

  // Resize the sprite.
	this->sprite.scale(0.1f,0.1f);

	// Set starting position(spawn)
	this->sprite.setPosition(target.getSize().x / 2.f - this->sprite.getGlobalBounds().width / 2,
		target.getSize().y / 2.f - this->sprite.getGlobalBounds().height / 2);
}

//Constructor
Player::Player(sf::RenderTarget& target)
{
	this->initVariables();
	this->initTexture();
	this->initSprite(target);
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

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

const bool Player::powerActive() const
{
	if (this->activePowerups.find(powerup::power) != this->activePowerups.end())
		return true;
	else
		return false;
}

const bool Player::shieldActive() const
{
	if (this->activePowerups.find(powerup::shield) != this->activePowerups.end())
		return true;
	else
		return false;
}

//Modifiers
void Player::setPos(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos.x,pos.y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int hp)
{
	this->hp -= hp;
	if (this->hp < 0)
		this->hp = 0;
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

void Player::absorbPowerup(PowerUp* power)
{
	switch (power->getType()) {
	case powerup::power:
		this->activePowerups[powerup::power] = 0.f;
		break;
	case powerup::health:
		this->hp = hpMax;
		break;
	case powerup::shield:
		this->activePowerups[powerup::shield] = 0.f;
		break;
    }
}


void Player::update()
{
	this->updateAttack();
	this->updatePowerups();
}

void Player::updateAttack()
{
	if(this->attackCooldownMax > this->attackCooldown)
	    this->attackCooldown += 0.5f;
}

void Player::updatePowerups()
{
	if (this->activePowerups.size() == 0)
		return;

	std::map<powerup, float>::iterator it = this->activePowerups.begin();

	for (it; it != this->activePowerups.end();) {

		if (it->second >= 1000.f) {
			it = this->activePowerups.erase(it);
		}
		else {
			it->second += 0.5f;
			++it;
		}
	}
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

//Destructor
Player::~Player()
{

}
