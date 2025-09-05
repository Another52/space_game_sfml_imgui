#pragma once

#include "util-includes.h"
#include "Player.hpp"

class Enemy
{
public:
	Enemy(sf::RenderWindow& window, sf::Texture& texture);
	void Update(Player& player, float dt);
	void Draw(sf::RenderWindow& window);
private:
	sf::Vector2i spawnLoc(int height, int width);
	int RandInRange(int min, int max);
public:
	sf::Sprite sprite;

	bool dead{false};
	float speed{0.8f};
	static constexpr float scale{ 5.f };
	static constexpr int spawn_margin = 100;
};