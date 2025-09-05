#include "Bullet.hpp"
#include <iostream>

Bullet::Bullet(Player& player, sf::Vector2i& mouse_pos)
{
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(shape.getGeometricCenter());
	shape.setPosition(player.getPosition());
	shape.setRotation(player.sprite.getRotation());
	dir = (static_cast<sf::Vector2f>(mouse_pos)-shape.getPosition()).normalized();
}

void Bullet::Update(sf::RenderWindow& window, float dt)
{
	/*if (sf::Keyboard::isKeyPressed(ssf::Keyboard::Key::W))
	{
		shape.move(sf::Vector2f(0.f, 1.f) * speed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		shape.move(sf::Vector2f(0.f, -1.f) * speed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		shape.move(sf::Vector2f(1.f, 0.f) * speed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		shape.move(sf::Vector2f(-1.f, 0.f) * speed * dt);
	}*/
	shape.move(dir * dt);

	sf::Vector2f pos = shape.getPosition();
	sf::Vector2u winSize = window.getSize();

	if (pos.x < 0 || pos.x > winSize.x || pos.y < 0 || pos.y > winSize.y)
	{
		dead = true;
	}

}

void Bullet::collidesWith(std::vector<Enemy>& enemies)
{
	for (Enemy& enemy : enemies)
	{

		if (shape.getGlobalBounds().findIntersection(enemy.sprite.getGlobalBounds()))
		{
			enemy.dead = true;
			dead = true;
			break;
		}
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}