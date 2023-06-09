#include "Game.h"

//Private Functions
void Game::initWindow()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	this->window = new sf::RenderWindow(sf::VideoMode(1000, 900),"Asteroids",sf::Style::Close | sf::Style::Titlebar,settings);
	this->window->setFramerateLimit(144);
}

void Game::initTextures()
{
	this->textures["LASER"] = new sf::Texture();
	this->textures["LASER"]->loadFromFile("Textures/normalLaser.png");

	this->textures["POWERFULLASER"] = new sf::Texture();
	this->textures["POWERFULLASER"]->loadFromFile("Textures/powerfulLaser.png");

	this->textures["BOOM1"] = new sf::Texture();
	this->textures["BOOM1"]->loadFromFile("Textures/boom1.png");

	this->textures["CRASH1"] = new sf::Texture();
	this->textures["CRASH1"]->loadFromFile("Textures/crash1.png");
}

void Game::initGUI()
{
	//Load font
	this->font.loadFromFile("Fonts/BrunoAce-Regular.ttf");

	//Init point text
	//this->pointText.setPosition(700.f,25.f );
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("points: ");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		                           this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	//Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 20.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 30.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

}

void Game::initWorld()
{
	// C:/Users/user/source/repos/Asteroids/Asteroids/src/
	this->worldBackgroundTex.loadFromFile("Textures/background1.jpg");
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initPlayer()
{
	this->player = new Player(*this->window);
}

void Game::initEnemies()
{
	this->spawnTimerMaxEnemies = 70.f;
	this->spawnTimerEnemies = 0.f;
}

void Game::initPowerups()
{
	this->spawnTimerPowerups = 0.f;
	this->spawnTimerMaxPowerups = 800.f;
}

//Constructors
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
	this->initEnemies();
	this->initPowerups();
	this->initGUI();
	this->initWorld();
}

//Functions
void Game::run()
{

	while(this->window->isOpen())
	{
		this->updatePollEvents();

		if(this->player->getHp() > 0)
		{
			this->update();
		}

		this->render();
	}

}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();

		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(
			(this->player->powerActive()) ? this->textures["POWERFULLASER"] : this->textures["LASER"], // texture
			this->player->getPos().x + this->player->getBounds().width/2.f, // spawn position X
			this->player->getPos().y, // spawn position Y
			0.f,   // travel direction X by
			-1.f, // travel direction Y by
			6.f, // travel speed
			(this->player->powerActive()) ? 6.f : 3.f) // damage
		); 
	}
}

void Game::updateGUI()
{
	//Update points text
	std::stringstream str;
	str << "Points: " << this->points;
	this->pointText.setString(str.str());

	//Update HP bar
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent,this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//Left screen side with player
	if(this->player->getBounds().left < 0.f)
	{
		this->player->setPos(sf::Vector2f(0.f, this->player->getBounds().top));
	}
	//Top screen side with player
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPos(sf::Vector2f(this->player->getBounds().left, 0.f));
	}
	//Right screen side with player
	if (this->player->getBounds().width + this->player->getPos().x > this->window->getSize().x)
	{
		this->player->setPos(sf::Vector2f(this->window->getSize().x - this->player->getBounds().width,this->player->getPos().y));
	}
	//Bottom screen side with player
	if (this->player->getBounds().height + this->player->getPos().y > this->window->getSize().y)
	{
		this->player->setPos(sf::Vector2f(this->player->getPos().x, this->window->getSize().y - this->player->getBounds().height));
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Is bullet off the screen
		if(bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimerEnemies += 0.5f;
	if (this->spawnTimerEnemies >= this->spawnTimerMaxEnemies)
	{
		float spawnXpos = rand() % this->window->getSize().x;

		if (spawnXpos >= this->window->getSize().x - 100.f)
			spawnXpos -= 300.f;

		this->enemies.push_back(new Enemy(spawnXpos, -200.f));
		this->spawnTimerEnemies = 0.f;
	}
  
	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//Check if Enemies colliding with the bottom of screen
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Lose Hp
			this->player->loseHp(4.f);

			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}
		//check if enemy colliding with the player
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			if (!this->player->shieldActive()) {
				this->explosions.push_back(new Explosion(*this->textures["CRASH1"], enemy->getPos()));
				this->player->loseHp(this->enemies.at(counter)->getDamage());
			}

			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);

			--counter;
		}

		++counter;
	}
}

void Game::updatePowerups()
{
	//Spawning
	this->spawnTimerPowerups += 0.5f;
	if (this->spawnTimerPowerups >= this->spawnTimerMaxPowerups)
	{
		float spawnXpos = rand() % this->window->getSize().x;

		if (spawnXpos >= this->window->getSize().x - 100.f)
			spawnXpos -= 300.f;

		this->powerups.push_back(new PowerUp(spawnXpos, -200.f));
		this->spawnTimerPowerups = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* powerup : this->powerups)
	{
		powerup->update();

		//Check if power up colliding with the bottom of screen
		if (powerup->getBounds().top > this->window->getSize().y)
		{

			//Delete power up
			delete this->powerups.at(counter);
			this->powerups.erase(this->powerups.begin() + counter);
			--counter;
		}
		//check if power up colliding with the player
		else if (powerup->getBounds().intersects(this->player->getBounds()))
		{
			this->player->absorbPowerup(powerup);

			delete this->powerups.at(counter);
			this->powerups.erase(this->powerups.begin() + counter);

			--counter;
		}

		++counter;
	}

}

void Game::updateCombat()
{

	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemyRemoved = false;

		for (int n = 0; n < this->bullets.size() && !enemyRemoved; n++)
		{
			if (this->bullets[n]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				this->enemies[i]->loseHp(this->bullets[n]->getDamage());

				delete this->bullets[n];
				this->bullets.erase(this->bullets.begin() + n);

				if (this->enemies[i]->getHp() == 0)
				{
					this->explosions.push_back(new Explosion(*this->textures["BOOM1"], this->enemies[i]->getPos()));

					this->points += this->enemies[i]->getPoints();

					delete this->enemies[i];
					this->enemies.erase(this->enemies.begin() + i);

					enemyRemoved = true;
				}
			}
		}
	}

}

void Game::updateExplosions()
{
	for(int i = 0;i < this->explosions.size();++i)
	{
		explosions[i]->update();

		if (explosions[i]->getLifeTimeOver())
		{
			delete explosions[i];
			explosions.erase(explosions.begin() + i);
			--i;
		}
	}
}

void Game::update()
{
	this->updateWorld();
	this->updateBullets();
	this->updateInput();
	this->player->update();
	this->updateCollision();
	this->updateEnemies();
	this->updatePowerups();
	this->updateCombat();
	this->updateExplosions();
	this->updateGUI();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	// Clear last frame
	this->window->clear();

	//Draw stuff
	this->renderWorld();

	for (auto* explosion : this->explosions)
	{
		explosion->render(this->window);
	}

	this->player->render(*this->window);

	for(auto* bullet : this->bullets)
	{
		bullet->render(*this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(*this->window);
	}

	for (auto* powerup : this->powerups)
	{
		powerup->render(*this->window);
	}

	this->renderGUI();

	//Game over
	if (this->player->getHp() <= 0)
		this->window->draw(this->gameOverText);

	//Display frame
	this->window->display();
}

//Destructor
Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for(auto& i : this->textures)
	{
		delete i.second;
	}

	//Delete Bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}

	//Delete enemies
	for (auto* enemy : this->enemies)
	{
		delete enemy;
	}
}
