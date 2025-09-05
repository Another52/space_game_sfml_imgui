#pragma once

#include "util-includes.h"

class Background
{
public:
	Background(sf::RenderWindow& window, sf::Texture& texture)
		:
		sprite(texture)
	{
		sprite.setOrigin(sprite.getGlobalBounds().getCenter());
		sprite.setPosition(static_cast<sf::Vector2f>(window.getSize()) / 2.f);
		sprite.setScale({ 5.f, 5.f });
	}
	void Update(float dt)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			sprite.move(sf::Vector2f(0.f, 1.f) * speed * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			sprite.move(sf::Vector2f(0.f, -1.f) * speed * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			sprite.move(sf::Vector2f(1.f, 0.f) * speed * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			sprite.move(sf::Vector2f(-1.f, 0.f) * speed * dt);
		}
	}
	void Draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}
public:
	sf::Sprite sprite;
	float speed{ 0.5f };
};