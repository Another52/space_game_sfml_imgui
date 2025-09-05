#include "Player.hpp"
#include <string>
using namespace sf::Literals;

Player::Player(sf::RenderWindow& window, sf::Texture& texture)
	:
	sprite(texture)
{
	int xIndex = 2;
	int yIndex = 0;

	int ssize = 16;
	sprite.setTextureRect(sf::IntRect(sf::Vector2i(xIndex * ssize, yIndex * ssize), sf::Vector2i(ssize, ssize)));
	sprite.scale({ scale, scale });
	sprite.setOrigin(sprite.getLocalBounds().getCenter());
	sprite.setPosition(static_cast<sf::Vector2f>(window.getSize()) / 2.f);
}

void Player::Update(sf::RenderWindow& window, float dt)
{
	//LookAt
	sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	sf::Vector2f dir = (mouse_pos - sprite.getPosition()).normalized();
	sprite.setRotation(sf::radians(std::atan2(dir.y, dir.x) - 80));

	//Keyboard Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		sprite.move(sf::Vector2f(0.f, -1.f) * speed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		sprite.move(sf::Vector2f(0.f, 1.f) * speed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		sprite.move(sf::Vector2f(-1.f, 0.f) * speed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		sprite.move(sf::Vector2f(1.f, 0.f) * speed * dt);
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}