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
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % 900, 0));
		this->spawnTimer = 0.f;
	}
  
	for(auto* enemy : this->enemies)
	{
		enemy->update();
	}
}

void Game::update()
{
	this->updatePollEvents();
	this->updateBullets();
	this->updateInput();
	this->player->update();
	this->updateEnemies();
}

void Game::render()
{
	// Clear last frame
	this->window->clear();

	//Draw stuff
	this->player->render(*this->window);

	for(auto* bullet : this->bullets)
	{
		bullet->render(*this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(*this->window);
	}

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
