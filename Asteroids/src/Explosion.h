#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdexcept>

class Explosion
{
private:
	sf::Sprite sprite;

	float lifeTime;
	float lifeTimeMax;

	bool lifeTimeOver;

	//Private Functions
	void initVariables();
public:
	//Constructors
	Explosion() = default;

	Explosion(sf::Texture& tex,const sf::Vector2f& pos);

	//Functions
	void update();

	void render(sf::RenderTarget* target);

	const bool getLifeTimeOver() const;

	//Destructor
	virtual ~Explosion();
};

#endif EXPLOSION_H
