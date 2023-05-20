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
   // Load a sshipTex from file.
	this->sshipTex.loadFromFile("Textures/ship.png"); // C:/Users/user/source/repos/Asteroids/Asteroids/src/
	this->shieldTex.loadFromFile("Textures/shieldTex.png");
}

void Player::initSprite(sf::RenderTarget& target)
{
  // Set textures to a sprites.
	this->sship.setTexture(this->sshipTex);
	this->shield.setTexture(this->shieldTex);

  // Resize the sprites.
	this->sship.scale(0.1f,0.1f);
	this->shield.scale(0.25f,0.25f);

	// Set starting position(spawn) of sprites
	this->sship.setPosition(target.getSize().x / 2.f - this->sship.getGlobalBounds().width / 2,
		target.getSize().y / 2.f - this->sship.getGlobalBounds().height / 2);

	this->shield.setPosition(target.getSize().x / 2.f - this->sship.getGlobalBounds().width / 2,
		target.getSize().y / 2.f - this->sship.getGlobalBounds().height / 2);
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
	return this->sship.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sship.getGlobalBounds();
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
	this->sship.setPosition(pos.x,pos.y);
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
	this->sship.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
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
	this->updateShieldPos();

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

		if (it->second >= 500.f) {
			it = this->activePowerups.erase(it);
		}
		else {
			it->second += 0.5f;
			++it;
		}
	}
}

void Player::updateShieldPos()
{
	this->shield.setPosition(sf::Vector2f(this->getPos().x - 27.f,
		this->getPos().y - 15.f));
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sship);

	if (this->shieldActive()) {
		target.draw(this->shield);
	}
}

//Destructor
Player::~Player()
{

}
