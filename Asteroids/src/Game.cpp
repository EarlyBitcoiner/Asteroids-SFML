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

//Constructors
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
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

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],this->player->getPos().x, this->player->getPos().y, 0.f, 0.f, 0.f));
	}
}

void Game::updateBullets()
{
	for (auto* bullet : this->bullets)
	{
		bullet->update();
	}
}

void Game::update()
{
	this->updatePollEvents();
	this->updateBullets();
	this->updateInput();
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
}
