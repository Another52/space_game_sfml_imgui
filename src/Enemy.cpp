#include "Enemy.hpp"
#include <string>
#include <iostream>


Enemy::Enemy(sf::RenderWindow& window, sf::Texture& texture)
	:
	sprite(texture)
{
	int xIndex = 0;
	int yIndex = 0;

	int ssize = 16;
	sprite.setTextureRect(sf::IntRect(sf::Vector2i(xIndex * ssize, yIndex * ssize), sf::Vector2i(ssize, ssize)));
	sprite.scale({ scale, scale });
	sprite.setOrigin(sprite.getLocalBounds().getCenter());
	
	int height = window.getSize().y;
	int width = window.getSize().x;
	sf::Vector2f spawn_loc = static_cast<sf::Vector2f>(spawnLoc(height, width));
	sprite.setPosition(spawn_loc);
}


void Enemy::Update(Player& player, float dt)
{
	//LookAt
	sf::Vector2f dir = (player.getPosition() - sprite.getPosition()).normalized();
	sprite.setRotation(sf::radians(std::atan2(dir.y, dir.x) + 90));

	//Keyboard input
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

	float move_to_player_speed = speed * 0.3 * dt;
	sprite.move(dir * move_to_player_speed);

	//player
	if (sprite.getLocalBounds().findIntersection(player.sprite.getLocalBounds()));
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

sf::Vector2i Enemy::spawnLoc(int height, int width)
{
	sf::Vector2i rand_pos{};
	enum Side { LEFT, RIGHT, TOP, BOTTOM };
	Side side = static_cast<Side>(rand() % 4);

	switch(side)
	{
		case LEFT:
		{
			rand_pos.x = RandInRange(-spawn_margin, -1);
			rand_pos.y = RandInRange(0, height - 1);
		}break;
		case RIGHT:
		{
			rand_pos.x = RandInRange(width, width + spawn_margin);
			rand_pos.y = RandInRange(0, height - 1);
		}break;
		case TOP:
		{
			rand_pos.x = RandInRange(0, width - 1);
			rand_pos.y = RandInRange(-spawn_margin, -1);
		}break;
		case BOTTOM:
		{
			rand_pos.x = RandInRange(0, width - 1);
			rand_pos.y = RandInRange(height, height + spawn_margin);
		}break;
	}

	return rand_pos;
}

int Enemy::RandInRange(int min, int max) {
	return min + rand() % (max - min + 1);
}