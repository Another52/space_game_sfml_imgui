#pragma once

#include "util-includes.h"

class Player
{
public:
	Player(sf::RenderWindow& window, sf::Texture& texture);
	void Update(sf::RenderWindow& window, float dt);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f getPosition() const
	{
		return sprite.getPosition();
	}
	void DamageHealth(float dt);
public:
	sf::Sprite sprite;
	sf::Texture texture;

	float speed{0.5f * 0.5f};
	float scale{ 5.f };
};