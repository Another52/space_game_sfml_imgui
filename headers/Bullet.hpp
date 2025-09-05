#include "util-includes.h"
#include "Player.hpp"
#include "Enemy.hpp"

class Bullet
{
public:
	Bullet(Player& player, sf::Vector2i& mouse_pos);
	void Update(sf::RenderWindow& window, float dt);
	void collidesWith(std::vector<Enemy>& enemies);
	void Draw(sf::RenderWindow& window);
	bool isDead() const
	{
		return dead;
	}
private:
	sf::CircleShape shape;
	sf::Vector2f lookat{};
	float speed{ 0.5f };
	sf::Vector2f dir{};
	bool dead{ false };
};