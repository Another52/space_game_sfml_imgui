#include "util-includes.h"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Background.cpp"
#include <iostream>


int main()
{
    //initialize
    unsigned int height = 1280;
    unsigned int width = 720;
    auto window = sf::RenderWindow(sf::VideoMode({height, width}), "Space Jam");
    window.setFramerateLimit(60);

    //---------------------initialize
    //texture and background
    sf::Texture spaceShip_tex;
    if (!spaceShip_tex.loadFromFile(std::string(RESOURCES_PATH) + "spaceShip/stitchedFiles/spaceships_c.png"))
        std::cout << "Player texture Not loaded: " << std::endl;

    sf::Texture bg_tex;
    bg_tex.setRepeated(true);
    if (!bg_tex.loadFromFile(std::string(RESOURCES_PATH) + "background1.png"))
        std::cout << "Background texture Not loaded: " << std::endl;
    Background bg(window, bg_tex);
    //texture and background

    Player player(window, spaceShip_tex);
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    enemies.reserve(10);
    //initialize
    
    //--------------------game loop
    sf::Clock clock;
    float enemy_spawn_timer = 0;
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asMilliseconds();
        //event handling
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    auto mousePos = sf::Mouse::getPosition(window);
                    bullets.emplace_back(player, mousePos);
                }
            }
        }

        //--------------Update
        bg.Update(deltaTime);
        //enemy
        if ((enemy_spawn_timer > 700 && (enemies.size() <= 10)) || enemies.size() < 2)
        {
            enemies.emplace_back(window, spaceShip_tex);
            enemy_spawn_timer = 0;
        }
        else
        {
            enemy_spawn_timer += deltaTime;
        }

        for (int i = enemies.size() - 1; i >= 0; --i)
        {
            enemies[i].Update(player, deltaTime);
            if(enemies[i].dead)
                enemies.erase(enemies.begin() + i);
        }
        
        //bullet update
        for (int i = bullets.size() - 1; i >= 0; --i)
        {
            bullets[i].Update(window, deltaTime);
            if (bullets[i].isDead())
                bullets.erase(bullets.begin() + i);
            bullets[i].collidesWith(enemies);
        }

        //player
        player.Update(window, deltaTime);

        //-----------------draw
        window.clear();
        bg.Draw(window);
        for (Enemy& enemy : enemies)
        {
            enemy.Draw(window);
        }
        for (Bullet& bullet : bullets)
        {
            bullet.Draw(window);
        }
        player.Draw(window);
        window.display();
        //draw
        
    }
}