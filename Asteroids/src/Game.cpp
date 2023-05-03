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
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("C:/Users/user/source/repos/Asteroids/Asteroids/src/Textures/bullet.png");
}

void Game::initGUI()
{
	//Load font
	this->font.loadFromFile("C:/Users/user/source/repos/Asteroids/Asteroids/src/Fonts/BrunoAce-Regular.ttf");

	//Init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(12);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

}

void Game::initWorld()
{
	this->worldBackgroundTex.loadFromFile("C:/Users/user/source/repos/Asteroids/Asteroids/src/Textures/background1.jpg");
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 80.f;
	this->spawnTimer = 0.f;
}

//Constructors
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
	this->initEnemies();
	this->initGUI();
	this->initWorld();
}

//Functions
void Game::run()
{

	while(this->window->isOpen())
	{
		this->update();
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
		this->bullets.push_back(new Bullet(this->textures["BULLET"],
			this->player->getPos().x + this->player->getBounds().width/2.f,
			this->player->getPos().y - this->player->getBounds().height/2.f,
			0.f,
			-1.f,
			5.f));
	}
}

void Game::updateGUI()
{

}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//Left screen side
	if(this->player->getBounds().left < 0.f)
	{
		this->player->setPos(sf::Vector2f(0.f, this->player->getBounds().top));
	}
	//Right screen side
	/*if (this->player->getBounds().width < 0.f)
	{
		this->player->setPos(sf::Vector2f(0.f, this->player->getBounds().top));
	}*/
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
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 40.f, -200.f));
		this->spawnTimer = 0.f;
	}
  
	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//Check if enemy off screen
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void Game::updateCombat()
{
	//Colicion check
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemyRemoved = false;
		//this->enemies[i]->update();

		for (int n = 0; n < this->bullets.size() && !enemyRemoved; n++)
		{
			if (this->bullets[n]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				delete this->bullets[n];
				delete this->enemies[i];

				this->bullets.erase(this->bullets.begin() + n);
				this->enemies.erase(this->enemies.begin() + i);
				enemyRemoved = true;
			}
		}
	}

}

void Game::update()
{
	this->updatePollEvents();
	this->updateWorld();
	this->updateBullets();
	this->updateInput();
	this->player->update();
	this->updateCollision();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
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

	this->player->render(*this->window);

	for(auto* bullet : this->bullets)
	{
		bullet->render(*this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(*this->window);
	}

	this->renderGUI();

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
