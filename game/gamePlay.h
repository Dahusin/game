#pragma once
#include <SFML/Graphics.hpp>
#include "classes\player.h"
#include "classes\fallingObject.h"
#include "classes\bullet.h"
#include <vector>
#include <ctime>
using namespace sf;

bool gamePlay(RenderWindow &window, Font font, int &score, int &goal, int &movingMode, int &shootingMode)
{
    srand(time(0));
    window.setFramerateLimit(60);

    Mouse::setPosition({950, 900});

    score = 0;
    Text scoreText(font);
    scoreText.setString(L"ОЧКИ: " + std::to_string(score));
    scoreText.setPosition({10, 750});

    Text exitText(font);
    exitText.setString(L"ВЫХОД");
    exitText.setPosition({1100, 750});

    Text goalText(font);
    goalText.setString(L"ЦЕЛЬ: " + std::to_string(goal));
    goalText.setPosition({600, 750});

    Texture gameBgTexture("game/images/gameBackground.png");
    Sprite gameBg(gameBgTexture);

    Texture gameBgTexture2("game/images/gameBackground2.png");
    Sprite gameBg2(gameBgTexture2);
    gameBg2.setPosition({0, 732});

    Image imagePlayer("game/images/planeSprite.png");
    imagePlayer.createMaskFromColor(Color::White);
    Texture texturePlayer(imagePlayer);
    Objects player(520, 620, 10, texturePlayer);

    std::vector<Bullet> bullets;
    Image imageBullet("game/images/bulletSprite.png");
    imageBullet.createMaskFromColor(Color::White);
    Texture textureBullet(imageBullet);

    std::vector<fallingObject> meteors;
    Image imageMeteor("game/images/meteorSprite.png");
    imageMeteor.createMaskFromColor(Color::White);
    Texture textureMeteor(imageMeteor);

    Clock reloadBullet;
    bool canShoot = true;

    Clock reloadMeteor;

    while (window.isOpen())
    {
        exitText.setFillColor(Color::White);
        if (exitText.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
            exitText.setFillColor(Color(236, 161, 149));
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
            if (event->is<Event::MouseButtonPressed>())
            {
                if (Mouse::isButtonPressed(Mouse::Button::Left) && exitText.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
                {
                    return false;
                }
            }
        }

        // Управление самолётом
        if (movingMode == 1)
        {
            if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left))
            {
                player.moveLeft();
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))
            {
                player.moveRight();
            }
        }
        else
        {
            Vector2i mousePosition = Mouse::getPosition(window);
            player.move(mousePosition);
        }

        // Стрельба + рел
        if (canShoot)
        {
            if (Keyboard::isKeyPressed(Keyboard::Key::Space) && shootingMode == 1 || Mouse::isButtonPressed(Mouse::Button::Left) && shootingMode == 2)
            {
                bullets.push_back(Bullet(player.getSprite().getPosition().x + 35, player.getSprite().getPosition().y, textureBullet));
                canShoot = false;
                reloadBullet.restart();
            }
        }

        if (reloadBullet.getElapsedTime().asSeconds() >= 0.25f)
        {
            canShoot = true;
        }

        for (auto &bullet : bullets)
        {
            bullet.update();
        }

        // Метеориты
        if (reloadMeteor.getElapsedTime().asSeconds() >= 0.65f)
        {
            meteors.push_back(fallingObject(rand() % 1120, -20.f, textureMeteor));
            reloadMeteor.restart();
        }

        for (auto &meteor : meteors)
        {
            meteor.update();
        }

        // Столкновения
        for (size_t i = 0; i < bullets.size(); ++i)
        {
            for (size_t j = 0; j < meteors.size(); ++j)
            {
                if (const std::optional intersection = bullets[i].getSprite().getGlobalBounds().findIntersection(meteors[j].getSprite().getGlobalBounds()))
                {
                    score++;
                    scoreText.setString(L"ОЧКИ: " + std::to_string(score));
                    bullets.erase(bullets.begin() + i);
                    meteors.erase(meteors.begin() + j);
                    if (score == goal)
                    {
                        goal += 10;
                        return false;
                    }
                    break;
                }
                if (meteors[j].getSprite().getPosition().y > 800)
                {
                    meteors.erase(meteors.begin() + j);
                }
            }
            if (bullets[i].getSprite().getPosition().y < -20)
            {
                bullets.erase(bullets.begin() + i);
            }
        }

        for (auto &meteor : meteors)
        {
            if (const std::optional intersection = player.getSprite().getGlobalBounds().findIntersection(meteor.getSprite().getGlobalBounds()))
            {
                return false;
            }
        }

        // Вывод на экране
        window.clear();

        window.draw(gameBg);
        window.draw(player.getSprite());

        for (auto &bullet : bullets)
        {
            window.draw(bullet.getSprite());
        }

        for (auto &meteor : meteors)
        {
            window.draw(meteor.getSprite());
        }

        window.draw(gameBg2);
        window.draw(scoreText);
        window.draw(goalText);
        window.draw(exitText);

        window.display();
    }

    return true;
}